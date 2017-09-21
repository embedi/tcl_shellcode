#**************************************************************************/
#                                                                         */
#    external declarations                                                */
#                                                                         */
#**************************************************************************/
    .globl _start
    
    .extern shellcode             # Defined in shellcode.c

    .extern _got_start            # Defined in raw.ld
    .extern _got_entry_count      # Defined in raw.ld

#**************************************************************************/
#                                                                         */
#    section declaration                                                  */
#                                                                         */ 
#**************************************************************************/

  
    .section ".load"


_start:

  mflr r4
  bl getpc

getpc:
  
  mflr r3
  mtlr r4
  
  mr r5, r3
  subi r5, r5, (getpc - _start)

  lis  r3, _got_start@ha
  addi r3, r3, _got_start@l

  lis  r4, _got_entry_count@ha
  addi r4, r4, _got_entry_count@l
  
  add       r10, r5, r3
  cmpwi     r4, 0
  beq       main
  li        r11, 0
  li        r9, 0
  subf      r4, r11, r4
  mtctr     r4

next_off:

  slwi      r9, r9, 2
  lwzx      r0, r10, r9
  add       r0, r0, r5
  stwx      r0, r10, r9
  addi      r11, r11, 1
  mr        r9, r11
  bdnz      next_off

main:

#**************************************
#    branch to main program
#***

  bl   shellcode

  twge r2, r2


# End of __start
