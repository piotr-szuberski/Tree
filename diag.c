#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "consts.h"
#include "structs.h"

extern bool diagnostic(int argc, char **argv) {
    bool diagnose;
    if (argc == NO_FLAG) {
        diagnose = false;
    }
    else if (argc > FLAG) {
        printf("ERROR - TOO MANY FLAGS\n");
        exit(1);
    }
    else {
        char *paramString = (char*) malloc((strlen(argv[1]) + 1)
            * sizeof(char));
        strcpy(paramString, argv[1]);
        if (((strlen(argv[1]) + 1) == FLAG_LENGTH) &&
            (paramString[0] == '-') && (paramString[1] == 'v')) {
            diagnose = true;
        }
        else {
            printf("ERROR - WRONG FLAG\n");
            exit(1);
        }
        free(paramString);
    }
    return diagnose;
}

extern void countNodesDiag(Tree *graph) {
    List helper;
    int nodes = 0;
    int stackCounter;
    StackT *s;

    initStack(&s);
    push(&s, graph[ARRAY_ZERO]->number);
    while (!isEmpty(s)) {
        stackCounter = pop(&s);
        nodes++;

        helper = graph[stackCounter]->rightest;
        while (helper != NULL) {
            push(&s, helper->node->number);
            helper = helper->next;
        }
    }
    removeStack(&s);
    fprintf(stderr, "NODES: %d\n", nodes);
}