#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consts.h"
#include "structs.h"

extern void createNode(int nodeNumber, int fatherNumber, Tree *new) {
    List newHimself = (List) malloc(sizeof(struct Cube));

    if (newHimself == NULL) {
        printf("NO MEMORY\n");
        exit(1);
    }

    *new = (Tree) malloc(sizeof(struct Node));
    if (*new == NULL) {
        printf("NO MEMORY\n");
        exit(1);
    }
    (*new)->number = nodeNumber;
    (*new)->father = fatherNumber;
    (*new)->rightest = (*new)->leftest = NULL;
    (*new)->himself = newHimself;
    newHimself->node = *new;
    newHimself->prev = newHimself->next = NULL;
}

extern void addNode(Tree *father, Tree *toAdd) {
    if ((*father)->rightest == NULL) {
        (*father)->rightest = (*father)->leftest = (*toAdd)->himself;
    }
    else {
        (*toAdd)->himself->next = (*father)->rightest;
        (*father)->rightest->prev = (*toAdd)->himself;
        (*father)->rightest = (*toAdd)->himself;
    }
    printf("OK\n");
}

extern void rightmostChild(List rightest) {
    if (rightest == NULL) {
        fprintf(stdout, "-1\n");
    }
    else {
        printf("%d\n", rightest->node->number);
    }
}

/* Deletes a node and changes father numbers of its childs */
extern void deleteNode(Tree child, Tree *father) {
    List forwardFather = child->himself->next;
    List backFather = child->himself->prev;

    if (child->rightest == NULL) {
        if (forwardFather != NULL) {
            forwardFather->prev = backFather;
        }
        else {
            (*father)->leftest = backFather;
        }
        if (backFather != NULL) {
            backFather->next = forwardFather;
        }
        else {
            (*father)->rightest = forwardFather;
        }
    }

    else {
        List changeFatherNumber = child->rightest;
        while (changeFatherNumber != NULL) {
            changeFatherNumber->node->father = (*father)->number;
            changeFatherNumber = changeFatherNumber->next;
        }

        child->rightest->prev = backFather;
        child->leftest->next = forwardFather;
        if (forwardFather != NULL) {
            forwardFather->prev = child->leftest;
        }
        else {
            (*father)->leftest = child->leftest;
        }
        if (backFather != NULL) {
            backFather->next = child->rightest;
        }
        else {
            (*father)->rightest = child->rightest;
        }
    }

    free(child->himself);
    free(child);
    printf("OK\n");
}

extern void deleteTree(Tree toUtilization, Tree *graph) {
    int stackCounter;
    List helper;
    StackT *s;

    initStack(&s);
    push(&s, toUtilization->number);

    while (!isEmpty(s)) {
        stackCounter = pop(&s);
        helper = graph[stackCounter]->rightest;

        while (helper != NULL) {
            push(&s, helper->node->number);
            helper = helper->next;
        }

        free(graph[stackCounter]->himself);
        free(graph[stackCounter]);
        graph[stackCounter] = NULL;
    }

    removeStack(&s);
}

extern void deleteSubTree(Tree toUtilization, Tree *father, Tree *graph) {
    List fatherForward = toUtilization->himself->next;
    List fatherPrevious = toUtilization->himself->prev;

    if (fatherForward != NULL) {
        fatherForward->prev = fatherPrevious;
    }
    else {
        (*father)->leftest = fatherPrevious;
    }

    if (fatherPrevious != NULL) {
        fatherPrevious->next = fatherForward;
    }
    else {
        (*father)->rightest = fatherForward;
    }

    deleteTree(toUtilization, graph);
    printf("OK\n");
}


/* Function adds a node to the right of its leftBrother and
 * makes all the nodes to the right of leftBrother its childs
 */
extern void splitNode(Tree *toAdd, Tree *father, List leftBrother) {
    if ((*father)->rightest == leftBrother) {
        (*toAdd)->himself->next = (*father)->rightest;
        (*father)->rightest->prev = (*toAdd)->himself;
        (*father)->rightest = (*toAdd)->himself;
    }
    else {
        List leftBrotherPrev = leftBrother->prev;
        while (leftBrotherPrev != NULL) {
            leftBrotherPrev->node->father = (*toAdd)->number;
            leftBrotherPrev = leftBrotherPrev->prev;
        }

        leftBrotherPrev = leftBrother->prev;
        (*toAdd)->himself->next = leftBrother;
        (*toAdd)->rightest = (*father)->rightest;
        (*toAdd)->leftest = leftBrotherPrev;
        leftBrotherPrev->next = NULL;
        (*father)->rightest = (*toAdd)->himself;
        leftBrother->prev = (*toAdd)->himself;
    }
    printf("OK\n");
}