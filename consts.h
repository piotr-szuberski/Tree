#ifndef CONSTS_H
#define CONSTS_H

#define FLAGS_NUMBER 1
#define FLAG1_CONDITION strlen(argv[1]) == 2 && \
            paramString[0] == '-' && \
            paramString[1] == 'v'
#define MAX_INPUT 40
#define ADD_NODE -2
#define DELETE_NODE -3
#define DELETE_SUBTREE -4
#define RIGHTMOST_CHILD -5
#define SPLIT_NODE -6
#define DO_ADD 'A'
#define DO_DELETE 'D'
#define DO_DELETE_NODE 'N'
#define DO_DELETE_SUBTREE 'S'
#define DO_RIGHTMOST 'R'
#define DO_SPLIT 'S'
#define WHICH_TO_DELETE 7

#endif /*CONSTS_H*/
