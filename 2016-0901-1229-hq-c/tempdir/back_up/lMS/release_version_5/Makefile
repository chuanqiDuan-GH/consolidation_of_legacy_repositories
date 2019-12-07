OBJ=lMS.o main.o menu.o

#$^是自动变量，代表所有不重复的目标依赖文件，所以定义完OBJ后，就可以使用代替OBJ，也就是代替众多.o依赖文件
lSM.out:$(OBJ)
	gcc $^ -o lSM.out	
#-std=c99 使用C99标准编译代码，因为C99允许在循环内定义变量
#或者gcc编译时使用-sts=gnu99 选项
lMS.o:lMS.c
	gcc -std=c99 -c lMS.c -I include
#-I选项代表去指定路径中找编译所需头文件，本句中的意思就是在当前目录下include文件中找编译相关头文件
main.o:main.c
	gcc -c main.c -I include
#编译子文件中的Makefile，需要用到make -C命令，一定要记住不是gcc -C，而是make -C命令
menu.o:
	make -C menu

#$(RM)也是一个自动变量，代表rm -f，下面的语句也就是rm -f *.o
.PHONY:clean
clean:
	$(RM) *.o
