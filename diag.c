#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "consts.h"
#include "structs.h"

/*Checks flags added to the program (only one flag = "-v"
 *or no flags allowed). Flag "-g" allows the diagnostic mode.
 */
extern bool diagnostic(int argc, char **argv) {
    bool diagnose;
    if (argc == 1) {
        diagnose = false;
    }
    else if (argc > FLAGS_NUMBER + 1) {
        printf("ERROR - TOO MANY FLAGS\n");
        exit(1);
    }
    else {
        char *paramString =
            (char*) malloc( (strlen(argv[1]) + 1) * sizeof(char));
        strcpy(paramString, argv[1]);
        if (FLAG1_CONDITION) {
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

/* Counts all the nodes in the tree */
extern void countNodesDiag(Tree *graph) {
    List helper;
    int nodes = 0;
    int stackCounter;
    StackT *s;

    initStack(&s);
    push(&s, graph[0]->number);
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