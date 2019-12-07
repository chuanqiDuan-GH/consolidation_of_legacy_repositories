OBJ=semaphore_sync.o server_shm.o

server.out:$(OBJ) 
	gcc $^ -c -I ../common -o server.out

server_shm.o:server_shm.c
	gcc -c server_shm.c -I ../common -o server_shm.o

semaphore_sync.o:
	make -C ../semaphore 

.PHONY:clean
clean:
	$(RM) *.o

