CPP = gcc
FLAGS = -Wall -std=c99 -pedantic -g 

EXEC = main
OBJS = linkedList.o main.o

default:${EXEC}

clean:
	rm -f ${EXEC}
	rm -f *.o

run: ${EXEC}
	./${EXEC}

valgrind: ${EXEC}
	valgrind --leak-check=full --track-origins=yes ./${EXEC}

${EXEC}:${OBJS}
	${CPP} ${FLAGS} -o ${EXEC} ${OBJS} -lm

.c.o:
	${CPP} ${FLAGS} -c $<

stack.o: linkedList.c linkedList.h
stackuser.o: main.c linkedList.h