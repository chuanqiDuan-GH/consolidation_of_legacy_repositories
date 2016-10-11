obj=command.o main.o
ser: $(obj)
	gcc -g $^ -o ser -lpthread -L/usr/include/myclient -lmysqlclient
command.o :command.c
	gcc -g -c command.c 
main.o : main.c 
	gcc -g -c main.c -lpthread
.PHONY:clean
clean: 
	rm *.o
