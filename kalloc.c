#include "kalloc.h"


void *kalloc(SceSize size, const char *name, int *id, int part, int type) 
{
    void *block = NULL;
    *id = sceKernelAllocPartitionMemory(part, name, type, size + 63, NULL);
    if(*id >= 0)
        block = sceKernelGetBlockHeadAddr(*id);
    return (void *)(((u32)block + 63) & ~63);
}
inline void kfree(int id) 
{
    sceKernelFreePartitionMemory(id);
}
void *kalloc_volatile() 
{
    void *block;
    int size;
    return !sceKernelVolatileMemTryLock(0, &block, &size) ? block : NULL;
}

inline void kfree_volatile() 
{
    sceKernelVolatileMemUnlock(0);
}