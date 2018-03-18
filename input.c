#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consts.h"

extern bool readInput(int *inputNode, int *leftBrother, int *command) {
    bool toNext = true;
    char *order;
    size_t max_size = MAX_INPUT;

    order = (char*) malloc(max_size * sizeof(char));
    if (order == NULL) {
        printf("NO MEMORY\n");
        exit(1);
    }

    order[0] = -1;
    order[WHICH_TO_DELETE] = -1;
    getline(&order, &max_size, stdin);

    switch (order[0]) {
        case DO_ADD:
            *command = ADD_NODE;
            sscanf(order, "ADD_NODE %d", inputNode);
            break;
        case DO_DELETE:
            if (order[WHICH_TO_DELETE] == DO_DELETE_NODE) {
                *command = DELETE_NODE;
                sscanf(order, "DELETE_NODE %d", inputNode);
            }
            else if (order[WHICH_TO_DELETE] == DO_DELETE_SUBTREE) {
                *command = DELETE_SUBTREE;
                sscanf(order, "DELETE_SUBTREE %d", inputNode);
            }
            break;
        case DO_RIGHTMOST:
            *command = RIGHTMOST_CHILD;
            sscanf(order, "RIGHTMOST_CHILD %d", inputNode);
            break;
        case DO_SPLIT:
            *command = SPLIT_NODE;
            sscanf(order, "SPLIT_NODE %d %d", inputNode, leftBrother);
            break;
        default:
            toNext = false;
            break;
    }
    free(order);
    return toNext;
}