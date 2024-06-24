#ifndef ARENA_INCLUDED
#define ARENA_INCLUDED
#include "except.h"

#define T Arena_T
typedef struct T *T;

#define ALLOC(a,b) Arena_alloc((a),(b),__FILE__,__LINE__)
#define CALLOC(a,b,c) Arena_calloc((a),(b),(c),__FILE__,__LINE__)
#define FREE(a) Arena_free((a))

extern const Except_T Arena_NewFailed;
extern const Except_T Arena_Failed;

extern T Arena_New(void);
extern void Arena_dispose(T *ap);
extern void *Arena_alloc(T arena,long nbytes,const char *file,int line);
extern void *Arena_calloc(T arena,long count,long nbytes,const char *file,int line);
extern void Arena_free(T arena);

#undef T
#endif
