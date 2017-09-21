/*
 * subsys.h
 */

#ifndef _SUBSYS_H
#define _SUBSYS_H

#define CISCO_SUBSYS_MAGIC 0xC15C0515

typedef enum
{
  Unknown = 0x0,
  Kernel = 0x10000,
  Library = 0x20000,
  Driver = 0x30000,
  Protocol = 0x40000,
  Management = 0x50000,
  Registry = 0x60000,
  SystemInit = 0x70000,
  EHSA = 0x80000,
  PreDriver = 0x90000,
  IFS = 0xA0000,
  Microcode = 0xB0000,
  PreEHSA = 0xC0000,
  License = 0xD0000,
} SUBSYSTEM_CLASS;


#pragma pack(push, 1)
typedef struct __attribute__((aligned(2)))
{
  unsigned int magic1;
  unsigned int magic2;
  unsigned int header_version;
  unsigned int kernel_majversion;
  unsigned int kernel_minversion;
  char* namestring;
  unsigned int subsys_majversion;
  unsigned int subsys_minversion;
  unsigned int subsys_editversion;
  void *init_address;
  SUBSYSTEM_CLASS _class;
  unsigned int _ID;
  char *properties_1;
  char *properties_2;
  char *properties_3;
  char *properties_4;
}subsystype;
#pragma pack(pop)

#endif				/* _SUBSYS_H */
