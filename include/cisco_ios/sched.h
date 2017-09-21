/*
 * sched.h
 */

#ifndef _SCHED_H
#define _SCHED_H

typedef enum 
{
  PROCESS_ANALYZE = 0x0,
  PROCESS_ARGS = 0x1,
  PROCESS_CRASHBLOCK = 0x2,
  PROCESS_PROPERTIES_3 = 0x3,
  PROCESS_NAME = 0x4,
  PROCESS_PID = 0x5,
  PROCESS_PRIORITY = 0x6,
  PROCESS_PROFILE = 0x7,
  PROCESS_RUNTIME = 0x8,
  PROCESS_SOCKETS = 0x9,
  PROCESS_STACK_SIZE = 0xA,
  PROCESS_PREFER = 0xB,
  PROCESS_TIMING = 0xC,
  PROCESS_TTYSOCK = 0xD,
  PROCESS_TTYNUM = 0xE,
  PROCESS_WAKEUP = 0xF,
  PROCESS_WATCHED_SIMPLE_TIMER = 0x10,
  PROCESS_11 = 0x11,
  PROCESS_PREFERS2 = 0x12,
  PROCESS_SCHEDTIME = 0x13,
  PROCESS_IMMORTAL = 0x14,
  PROCESS_15 = 0x15,
} PROCESS_PROPERTIES;

typedef enum
{
  PROC_PRIORITY_PREEMPTIVE = 0x1,
  PROC_PRIORITY_CRITICAL = 0x2,
  PROC_PRIORITY_HIGH = 0x3,
  PROC_PRIORITY_NORMAL = 0x4,
  PROC_PRIORITY_LOW = 0x5,
  PROC_PRIORITY_PREEMPTIVE_ION = 0x6,
} PROC_PRIORITY;


typedef void* (*process_pcb_by_pid)(int pid);
typedef int (*process_create)(void *entry_point, char* name, int stack_size, int priority);
typedef int (*process_set_properties)(int property, int pid, int value);
typedef int (*process_kill)(int pid);

#endif				/* _SCHED_H */
