OBJ=main.o func.o

lots.out:$(OBJ)
	gcc $^ -o lots.out -lpthread

main.o:main.c
	gcc -c main.c

func.o:func.c
	gcc -c func.c

.PHONY:clean
clean:
	$(RM) *.o *.out
