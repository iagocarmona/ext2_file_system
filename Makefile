all:
	gcc -g -c utils/utils.c 
	gcc -g -c main.c
	gcc -g -c StackDirectory/stackDirectory.c
	gcc -g -c ListDirEntry/listDirEntry.c
	gcc -g -c commands/attr/attr.c
	gcc -g -c commands/cat/cat.c
	gcc -g -c commands/cd/cd.c
	gcc -g -c commands/help/help.c
	gcc -g -c commands/info/info.c
	gcc -g -c commands/ls/ls.c
	gcc -g -c commands/pwd/pwd.c
	gcc -o main *.o -lm

clean: 
	rm *.o main