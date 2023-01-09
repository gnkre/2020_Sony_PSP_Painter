#ifndef KALLOC_H_
#define KALLOC_H_

#include <pspsysmem.h>
#include <pspsuspend.h>

void *kalloc(SceSize size, const char *name, int *id, int part, int type);
void kfree(int id);
void *kalloc_volatile();
void kfree_volatile();
#endif