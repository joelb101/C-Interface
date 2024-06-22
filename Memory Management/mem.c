#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "Assert.h"
#include "except.h"
#include "mem.h"

#define NDESCRIPTORS 512
#define hash(p,t) (((unsigned long)(p)>>3)&\
				(sizeof(t)/sizeof((t)[0])-1))
#define NALLOC ((4096 + sizeof(union align)-1)/(sizeof(union align)))*(sizeof(union align))


const Except_T Mem_failed = {"Allocate Failed"};

/**
*this is a memory allocator that sits on top of library
*functions. The allocator maintains a hash table of
*block descriptors.
*Fields in the descriptor:
*  - ptr: contains the adress of the block that is allocated
*  - size: contains the size of the block allocated
*  - free: cicular list maintaining free blocks
*  - link: list maintaing allocated blocks
*/
static struct descriptor{
	struct descriptor *free;
	struct descriptor *link;
	const void *ptr;
	long size;
	const char *file;
	int line;
}*htab[2048];

static struct  descriptor freelist = {&freelist};

union align{
	int i;
	long l;
	long *lp;
	void *p;
	void (*fp)(void);
	float f;
	double d;
	long double ld;
};


/**search for the descriptor
*input: pointer
*return: pointer to the descriptor or NULL
*/
static struct descriptor *find(const void *ptr){
	struct descriptor *bp = htab[hash(ptr,htab)];
	
	while(bp && bp->ptr != ptr)
		bp=bp->link;
	return bp;
}

static struct descriptor *dalloc(void *ptr,long size,const char *file,int line){
	static struct descriptor *avail;
	static int nleft;
	
	if(nleft <=0){
		avail = malloc(NDESCRIPTORS*sizeof(*avail));
		if(avail==NULL)
			return NULL;
		nleft = NDESCRIPTORS;
	}
	avail->ptr = ptr;
	avail->size = size;
	avail->file = file;
	avail->line = line;
	avail->free = avail->link = NULL;
	nleft--;
	return avail++;;;;
}

void *Mem_alloc(long nbytes,const char *file,int line){
	struct descriptor *bp;
	void *ptr;
	
	Assert(nbytes>0);
	nbytes = ((nbytes + sizeof(union align)-1)/(sizeof(union align)))*(sizeof(union align));
	
	for(bp=freelist.free;bp;bp=bp->free){
		if(bp->size > nbytes){
			bp->size -= nbytes;
			ptr = (char*)bp->ptr + bp->size;
			if( (bp = dalloc(ptr,nbytes,file,line)) != NULL){
				unsigned h = hash(ptr,htab);
				bp->link = htab[h];
				htab[h] = bp;
				return ptr;
			}
			else{
				if(file==NULL)
					RAISE(Mem_failed);
				else
					Except_raise(&Mem_failed,file,line);
			}
		}
		if(bp == &freelist){
			struct descriptor *newptr;
			if( (ptr = malloc(nbytes+NALLOC)) == NULL || (newptr = dalloc(ptr,nbytes+NALLOC,__FILE__,__LINE__)) == NULL ){
				if(file==NULL)
					RAISE(Mem_failed);
				else
					Except_raise(&Mem_failed,file,line);
			}
			newptr->free = freelist.free;
			freelist.free = newptr;
		}
	}
	Assert(0);
	return NULL;
}

//Raises an exception if ptr isnot a valid pointer
void Mem_free(void *ptr,const char *file,int line){
	if(ptr){
		struct descriptor *bp;
		if( ((unsigned long)ptr)%(sizeof(union align)) != 0 || (bp = find(ptr)) == NULL || bp->free)
			Except_raise(&Assert_Failed,file,line);
		bp->free = freelist.free;
		freelist.free = bp;
	}
}

void *Mem_resize(void *ptr,long nbytes,const char *file,int line){
	struct descriptor *bp;
	void *newptr;
	
	Assert(ptr);
	Assert(ptr>0);
	
	if( ((unsigned long)ptr)%(sizeof(union align)) != 0 || (bp = find(ptr)) == NULL || bp->free)
			Except_raise(&Assert_Failed,__FILE__,__LINE__);
	
	newptr = Mem_alloc(nbytes,file,line);
	memcpy(newptr,ptr,nbytes<bp->size? nbytes : bp->size);
	Mem_free(ptr,file,line);
	return newptr;
}

void *Mem_calloc(long count,long nbytes,const char *file,int line){
	void *ptr;
	Assert(count>0);
	Assert(nbytes>0);
	ptr = Mem_alloc(count*nbytes,file,line);
	memset(ptr,'\0',count*nbytes);
	return ptr;
}











	
	
	
	
	
	
	
	
	
	
	
	
	
	

