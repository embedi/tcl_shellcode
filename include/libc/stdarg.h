#ifndef _STDARG_H
#define _STDARG_H

//typedef char *  va_list;

#if (__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 96))

typedef __builtin_va_list va_list;
#define va_start(v,l)	__builtin_va_start((v),(l))
#define va_end		__builtin_va_end
#define va_arg		__builtin_va_arg
#define __va_copy(d,s)	__builtin_va_copy((d),(s))

#endif

#endif				/* _STDARG_H */
