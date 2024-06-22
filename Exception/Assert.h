#undef Assert
#ifdef NDEBUG
#define Assert(e) ((void)0)
#else
#include "except.h"
extern void Assert(int e);
#define Assert(e) ((void)((e)||(RAISE(Assert_Failed),0)))
#endif
