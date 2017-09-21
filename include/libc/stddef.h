#ifndef _STDDEF_H
#define _STDDEF_H

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

typedef unsigned int size_t;

#endif				/* _STDDEF_H */
