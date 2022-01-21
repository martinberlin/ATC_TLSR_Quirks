//#include <stdio.h>
#include <stddef.h>
#include "mini_malloc.h"

struct mblock *mini_free_list = (void*)memory;

void mini_initialize(){
 mini_free_list->size=5000-sizeof(struct mblock);
 mini_free_list->free=1;
 mini_free_list->next=NULL;
}

void mini_split(struct mblock *fitting_slot,int size){
 struct mblock *new=(void*)((void*)fitting_slot+size+sizeof(struct mblock));
 new->size=(fitting_slot->size)-size-sizeof(struct mblock);
 new->free=1;
 new->next=fitting_slot->next;
 fitting_slot->size=size;
 fitting_slot->free=0;
 fitting_slot->next=new;
}


void *mini_malloc(int noOfBytes){
 struct mblock *curr,*prev;
 void *result;
 if(!(mini_free_list->size)){
  mini_initialize();
  printf("Memory initialized\n");
 }
 curr=mini_free_list;
 while((((curr->size)<noOfBytes)||((curr->free)==0))&&(curr->next!=NULL)){
  prev=curr;
  curr=curr->next;
  printf("One mblock checked\n");
 }
 if((curr->size)==noOfBytes){
  curr->free=0;
  result=(void*)(++curr);
  printf("Exact fitting mblock allocated\n");
  return result;
 } else if((curr->size)>(noOfBytes+sizeof(struct mblock))){
  mini_split(curr,noOfBytes);
  result=(void*)(++curr);
  printf("Fitting mblock allocated with a split\n");
  return result;
 } else{
  result=NULL;
  printf("Sorry. No sufficient memory to allocate\n");
  return result;
 }
}

void mini_merge(){
 struct mblock *curr,*prev;
 curr=mini_free_list;
 while((curr->next)!=NULL){
  if((curr->free) && (curr->next->free)){
   curr->size+=(curr->next->size)+sizeof(struct mblock);
   curr->next=curr->next->next;
  }
  prev=curr;
  curr=curr->next;
 }
}

void mini_free(void* ptr){
 if(((void*)memory<=ptr)&&(ptr<=(void*)(memory+20000))){
  struct mblock* curr=ptr;
  --curr;
  curr->free=1;
  mini_merge();
 }
 else printf("Please provide a valid pointer allocated by MyMalloc\n");
}
