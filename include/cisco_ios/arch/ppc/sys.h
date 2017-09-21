/*
 * sys.h
 */

#ifndef _SYS_H
#define _SYS_H

static inline void _putc(char ch)
{
  __asm__ volatile 
  (
    "li  r3, 1        \n\t"
    "mr  r4, %[aCh]   \n\t"
    "sc               \n\t"

    :                 /* output */
    :[aCh] "r" (ch)   /* input */
    :"r3", "r4"       /* clobbered register */
  );
}

static inline void reset()
{
  __asm__ volatile
  (
    "li r3, 0x8   \n\t"
    "sc           \n\t"
  );
}

static inline void confreg(int value)
{
  __asm__ volatile
  (
    "li r3, 0x30      \n\t"
    "mr r4, %[aValue] \n\t"
    "sc               \n\t"
    
    :                       /* output */
    :[aValue] "r" (value)   /* input */
    :"r3", "r4"             /* clobbered register */
  );
}

static inline  unsigned int get_pc()
{
  unsigned int pc;

  __asm__ volatile
  (
    "   mflr r4         \n\t"
    "   bl   1f         \n\t"
    "1:                 \n\t"
    "   mflr r3         \n\t"
    "   mtlr r4         \n\t"
    "   mr   %[aPC], r3 \n\t"
    
    :[aPC] "=r" (pc)    /* output */
    :                   /* input */
    :"r3", "r4"         /* clobbered register */
  );

  return pc;
}

static inline void breakpoint()
{
  __asm__ volatile
  (
    "twge r2, r2  \n\t"
  );
}

#endif				/* _SYS_H */
