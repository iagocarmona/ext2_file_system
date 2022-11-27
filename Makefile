all:
	gcc -g -c utils/utils.c 
	gcc -g -c main.c
	gcc -o main *.o -lm

clean: 
	rm *.o main