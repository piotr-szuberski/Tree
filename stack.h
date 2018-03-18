#ifndef STACK_H
#define STACK_H

#include "structs.h"

extern void initStack(StackT **stack);

extern void push(StackT **stack, int x);

extern bool isEmpty(StackT *stack);

extern int pop(StackT **stack);

extern void removeStack(StackT **stack);

#endif /*STACK_H*/
