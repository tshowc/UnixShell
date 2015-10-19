mysh: mysh.c
	gcc -std=gnu11 -g -o mysh mysh.c 

clean: 
	rm -f mysh
