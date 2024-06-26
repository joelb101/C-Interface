#ifndef MEM_INCLUDED
#define MEM_INCLUDED
#include "except.h"


#define ALLOC(nbytes)\
				Mem_alloc((nbytes),__FILE__,__LINE__)
#define CALLOC(count,nbytes)\
				Mem_calloc((count),(nbytes),__FILE__,__LINE__)
#define NEW(p)\
				((p) = ALLOC((long)sizeof(*(p))))
#define NEW0(p)\
				((p) = CALLOC(1,(long)sizeof(*(p))))
#define FREE(p)\
				((void)Mem_free((p),__FILE__,__LINE__)),((p)=0)
#define RESIZE(ptr,nbytes)\
				((ptr) = Mem_resize((ptr),\
				(nbytes),__FILE__,__LINE__))                    


//error thrown when allocation fails
extern const Except_T Mem_failed;

//allocates a block of atleast nbytes and returns a pointer to first byte
extern void *Mem_alloc(long nbytes,const char *file,int line);

//allocates a block large enough to hold atleat count items, each of size nbytes
extern void *Mem_calloc(long count,long nbytes,const char *file,int line);

extern void Mem_free(void *ptr,const char *file,int line);

extern void *Mem_resize(void *ptr,long nbytes,const char *file,int line);

#endif
