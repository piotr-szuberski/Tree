all: solution
solution: tree.o diag.o execute.o solution.o input.o stack.o
	gcc -pedantic -std=c99 -o solution tree.o diag.o execute.o stack.o solution.o input.o

tree.o: tree.c consts.h structs.h
	gcc -c tree.c
diag.o: diag.c consts.h structs.h
	gcc -c diag.c
execute.o: execute.c consts.h structs.h
	gcc -c execute.c
input.o: input.c consts.h
	gcc -c input.c
solution.o: solution.c execute.h diag.h
	gcc -c solution.c
stack.o: stack.c consts.h structs.h
	gcc -c stack.c

debug: solutiondbg
solutiondbg: tree.dbg diag.dbg execute.dbg solution.dbg input.dbg stack.dbg
	gcc -g -pedantic -std=c99 -Wall -Werror -o solution.dbg tree.o diag.o execute.o stack.o solution.o input.o

tree.dbg: tree.c consts.h structs.h
	gcc -g -c tree.c
diag.dbg: diag.c consts.h structs.h
	gcc -g -c diag.c
execute.dbg: execute.c consts.h structs.h
	gcc -g -c execute.c
input.dbg: input.c consts.h
	gcc -g -c input.c
stack.dbg: stack.c consts.h structs.h
	gcc -g -c stack.c
solution.dbg: solution.c execute.h diag.h
	gcc -g -c solution.c


clean:
	rm tree.o
	rm stack.o
	rm execute.o
	rm solution.o
	rm diag.o
	rm input.o
	rm solution
	rm solution.dbg
