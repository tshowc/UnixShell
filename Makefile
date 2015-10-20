mysh: mysh.c
	gcc -std=gnu11 -w -g -o mysh mysh.c 

clean: 
	rm -f mysh
