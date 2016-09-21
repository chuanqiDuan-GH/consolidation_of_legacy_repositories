OBJ=linkList.o main.o

link.out:$(OBJ)
	gcc $^ -o link.out

#gcc -c仅编译 不链接 这个是重点 要记住 Makefile中要这样写
#gcc -c linkList.c与gcc -c linkList.c -o linkList.o执行结果一致
linkList.o:linkList.c
	gcc -c linkList.c -o linkList.o
main.o:main.c
	gcc -c main.c -o main.o

.PHONY:clean
clean:
	$(RM) *.o

