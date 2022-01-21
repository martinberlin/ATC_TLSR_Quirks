#pragma once
#include <stddef.h>
#include "application/print/u_printf.h"

char memory[5000];

struct mblock{
 int size;
 int free;
 struct mblock *next; 
};

void mini_initialize();
void mini_split(struct mblock *fitting_slot,int size);
void *mini_malloc(int noOfBytes);
void mini_merge();
void mini_free(void* ptr);
