/*
 * ppc_ebook_mmu.h
 */

#ifndef _PPC_EBOOK_MMU_H
#define _PPC_EBOOK_MMU_H

#define FIXED_SIZE_TLB 0x01
#define MAX_TLB1_INDEX 0x0F

typedef struct
{
  unsigned long rsrv32_34: 3;
  unsigned long tlbsel: 1;       // selects TLB to access
  unsigned long rsv36_43: 8;
  unsigned long esel: 4;         // entry select
  unsigned long rsv48_62: 15;
  unsigned long nv: 1;           // next victim
}__attribute__((packed)) _MAS0;

typedef union
{
  unsigned long value;
  _MAS0 bitfield;
} MAS0;

typedef struct
{
  unsigned long v: 1;           // TLB valid bit
  unsigned long iport: 1;       // invalidate protect
  unsigned long rsv34_39: 6;
  unsigned long tid: 8;         // translation identity
  unsigned long rsv48_50: 3;
  unsigned long ts: 1;          // translation space
  unsigned long tsize: 4;       // translation size
  unsigned long rsv56_63: 8;
  
}__attribute__((packed)) _MAS1;


typedef union
{
  unsigned long value;
  _MAS1 bitfield;
} MAS1;

typedef struct
{
  unsigned long epn: 20;        // effective page number
  
  unsigned long rsrv52_56: 5;
  
  unsigned long X2: 1;          // implementetion-dependent
  unsigned long X1: 1;          // implementetion-dependent
  
  unsigned long W: 1;           // write-through
  unsigned long I: 1;           // caching-inhibited
  unsigned long M: 1;           // memory coherency
  unsigned long G: 1;           // guarded
  unsigned long E: 1;           // endianness

}__attribute__((packed)) _MAS2;

typedef union
{
  unsigned long value;
  _MAS2 bitfield;
} MAS2;


typedef struct
{

  unsigned long rpn: 20;        // real page number
  unsigned long rsv52_53: 2;

  unsigned long u0: 1;          // user attribute bits
  unsigned long u1: 1;
  unsigned long u2: 1;
  unsigned long u3: 1;

  unsigned long ux: 1;          // user execute
  unsigned long sx: 1;          // supervisor execute

  unsigned long uw: 1;          // user write
  unsigned long sw: 1;          // supervisor write

  unsigned long ur: 1;          // user read
  unsigned long sr: 1;          // supervisor read
}__attribute__((packed)) _MAS3;

typedef union
{
  unsigned long value;
  _MAS3 bitfield;
} MAS3;

typedef struct
{
  unsigned long reserved: 28;
  unsigned long rpn: 4;
}__attribute__((packed)) _MAS7;

typedef union
{
  unsigned long value;
  _MAS7 bifield;
} MAS7;


typedef struct
{
  MAS0 mas0;
  MAS1 mas1;
  MAS2 mas2;
  MAS3 mas3;
  MAS7 mas7;
} MMU;

typedef struct
{
  unsigned long start;
  unsigned long end;
  unsigned long size;
  unsigned char is_code;
  unsigned char is_readable;
} memregion;

typedef struct {
  memregion virt;
  memregion phys;
  unsigned char wimges;
  unsigned char attr;
} tlb_entry;


static inline void read_tlb_entry(unsigned char tlb, unsigned char index, MMU* mmu)
{
  MAS0 mas0; mas0.value = 0;

  mas0.bitfield.tlbsel = tlb; 
  mas0.bitfield.esel   = index;

  __asm__ volatile 
  (
    ".equ MAS0, 0x270        \n\t"
    ".equ MAS1, 0x271        \n\t"
    ".equ MAS2, 0x272        \n\t"
    ".equ MAS3, 0x273        \n\t"
    ".equ MAS7, 0x3B0        \n\t"
    
    "mr        r0, %[aValue] \n\t"
    "mtspr     MAS0, r0      \n\t"
    "tlbre     r0, r0, 0     \n\t"

    "mfspr     r0, MAS0      \n\t"
    "stw       r0, %[aMAS0]  \n\t" //    "mr       %[aMAS0], r0   \n\t"

    "mfspr     r0, MAS1      \n\t"
    "mr        %[aMAS1], r0  \n\t"

    "mfspr     r0, MAS2      \n\t"
    "mr        %[aMAS2], r0  \n\t"

    "mfspr     r0, MAS3      \n\t"
    "mr        %[aMAS3], r0  \n\t"

    "mfspr     r0, MAS7      \n\t"
    "mr        %[aMAS7], r0  \n\t"

    :[aMAS0] "=mr" (mmu->mas0.value),
     [aMAS1] "=mr" (mmu->mas1.value),
     [aMAS2] "=mr" (mmu->mas2.value),
     [aMAS3] "=mr" (mmu->mas3.value),
     [aMAS7] "=mr" (mmu->mas7.value)  /* output */
    :[aValue] "r" (mas0.value)        /* input */
    :"r0"                             /* clobbered register */
  );
}

#endif				/* _PPC_EBOOK_MMU_H */
