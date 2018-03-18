#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"

extern void initStack(StackT **stack) {
    *stack = NULL;
}

extern void push(StackT **stack, int x) {
    StackT *temporary = (StackT*) malloc(sizeof(StackT));

    if (temporary == NULL) {
        printf("NO MEMORY\n");
        exit(1);
    }

    temporary->next = *stack;
    temporary->value = x;
    *stack = temporary;
}

extern bool isEmpty(StackT *stack) {
    return (stack == NULL);
}

extern int pop(StackT **stack) {
    int value;
    StackT *temporary;
    if (isEmpty(*stack)) {
        printf("ERROR - STACK EMPTY\n");
        exit(1);
    }
    value = (*stack)->value;
    temporary = *stack;
    *stack = (*stack)->next;
    free(temporary);
    return value;
}

extern void removeStack(StackT **stack) {
    StackT *temporaryBack;
    StackT *temporary = *stack;

    while (temporary != NULL) {
        temporaryBack = temporary;
        temporary = temporary->next;
        free(temporaryBack);
    }
}