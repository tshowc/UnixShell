#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

//SINGLY LINKED LIST STRUCTURES

/*typedef struct ll_node{
    struct ll_node *next;
    char *token;
}ll_node;

typedef struct ll{
    struct ll_node *head;
    int count;
}ll;   


//SINGLY LINKED LIST FUNCTIONS


ll_node* ll_node_init(char *t){
    ll_node *node = malloc(sizeof(ll_node));
    node->next = NULL;
    node->token = t;
    return node;
};

ll* ll_init(){
    ll *list = malloc(sizeof(ll));
    list->count = 0;
    return list;
};*/

/*int ll_node_init(ll_node **node, char *t){
    *node = malloc(sizeof(ll_node));
    if(node != NULL){
        node->next = NULL;
        node->token = t;
        return 1; //SUCCESS
    }
    else{
        return 0; //FAILURE
    }   
};

int ll_init(ll **list){
    *list = malloc(sizeof(ll));
    if(list != NULL){
        list->head = NULL;
        list->count = 0;
        return 1;
    }
    else{
        return 0;
    }    
};*/

//Adds command token to list
/*void add(char *t, ll *list){
    ll_node *node = ll_node_init(t);
    ll_node *temp;
    if(list->count == 0){
        list->head = node;
        list->count++;
    }   
    else{
        temp = list->head;
        for(int i=0; i <= list->count; i++){
           temp = temp->next;
        }
        temp->next = node;
        list->count++;  
    } 
};    

//Retrieves command tokens from beginning of list and deletes node
char * retrieve(ll *list){
    ll_node *temp;
    char *argv = list->head->token;
    temp = list->head;
    list->head = list->head->next;
    free(temp);
    return argv;

};*/    



//Test if a command is built in command or not
int builtinCommands(char *c)
{

//	printf("IN BUILD IN CHECK");
    int isBuiltIn = 0;

   if( ((strcmp(c, "exit") == 0) || (strcmp(c, "pwd") == 0)) || ((strcmp(c, "cd") == 0) || (strcmp(c, "wait") == 0))){
//    printf("%s and exit compared to %d\n", c, strcmp(c,"exit")); 
//    printf("%s and pwd compared to %d\n", c, strcmp(c,"pwd")); 
//    printf("%s and cd compared to %d\n", c, strcmp(c,"cd")); 
//    printf("%s and wait compared to %d\n", c, strcmp(c,"wait")); 
	isBuiltIn = 1;
   }

    return isBuiltIn;  
}    


void callBuiltIns(char *c, char *arr[])
{
//    printf("THIS IS C %s\n", c);
    if(strcmp(c, "exit")  == 0)
    {
        callExit();
    }
    else if(strcmp(c, "pwd") == 0)
    {
        callPwd();
    }    
    else if(strcmp(c, "cd") == 0)
    {
        callCd(arr);
    }    
    else if(strcmp(c, "wait") == 0)
    {
        callWait();
    }
    else
    {
//        printf("ERROR THIS IS NOT A BUILTIN COMMAND.\n");
    }    

}    


int callExit()
{
    exit(0);
}   

int callPwd()
{
    char *cwd;
    char buff[PATH_MAX + 1];

    cwd = getcwd( buff, PATH_MAX + 1);
    if(cwd != NULL) {
        printf("%s\n", cwd );
    }
    return EXIT_SUCCESS;    
}   


int callCd(char *arr[])
{
 char error_message[30] = "An error has occurred\n";	
 if((arr != NULL) && (arr[0] == '\0')){
//	printf("ARRAY IS EMPTY\n");
 	const char* home = getenv("HOME");
 	if(chdir(home) == 0){
 	    printf("Directory is now %s\n", home);
 	    return EXIT_SUCCESS;

 	}
 	else{
		write(STDERR_FILENO, error_message, strlen(error_message));
// 	    printf("File directory %s not found.\n", home); 
 	    return EXIT_FAILURE;
 	}
 }
 else{
//	if(arr[1] == '\0'){	 
		 callCdPath(arr[0]);
//	}
//	else{
//		printf("Invalid arguments: ");
//		int i;
//		for(i = 0; arr[i] != '\0'; i++){
//			printf("arr[%d] %s, ",i, arr[i]);
//		}
//	}
 }

}

int callCdPath(char *path)
{
	char error_message[30] = "An error has occurred\n";
	char *cash = "$";	
	if(strstr(path, cash) == NULL){    
		
		if(chdir(path) == 0){
    	    printf("Directory is now ");
    	    callPwd();
    	    return EXIT_SUCCESS;
    	}
    	else{
			write(STDERR_FILENO, error_message, strlen(error_message));
//    	    printf("File directory %s not found.\n", path); 
    	    return EXIT_FAILURE; 
    	}
	}
	else{
		char *env;	
		char *delim = "$";
		env = strtok(path, delim);
		int i;
		for(i=0; env[i] != NULL; i++){
			env[i] = toupper(env[i]);
		}
	//	printf("THIS IS ENV: %s\n", env);
		if(chdir(getenv(env)) == 0){
			printf("Directory is now ");
			callPwd();
			return EXIT_SUCCESS;
		}
		else{
			write(STDERR_FILENO, error_message, strlen(error_message));
	//		printf("Environment path %s not found.\n", path);
		}
	}
		
}    



int callWait()
{

}    


int main(int argc, char *argv[])
{
	char error_message[30] = "An error has occurred\n";
	/*int child;
	char input[100];
	char *cmd;
	char *cmdArr[100];
	char *token;
	char *savedcmd;
	int count = 0; 
	char *delim = " \t\r\n\f\v";*/
/*	printf("ARGC: %d\n", argc);
	int i = 0;
	for(i = 0; argv[i] != '\0'; i++){
			printf("ARGV %d is %s\n", i, argv[i]);
	}*/
	char *batchfile;
	FILE *bf;
	if(argc == 2){
		batchfile = argv[1];
		bf = fopen(batchfile, "r");
		if(bf == NULL){
				write(STDERR_FILENO, error_message, strlen(error_message));
			//	fprintf(stderr, "CANNOT OPEN FILE '%s'. EXITING.\n", batchfile);
				exit(1);
		}
	}
	else if(argc > 2){
		write(STDERR_FILENO, error_message, strlen(error_message));
		exit(1);
	}
    while(1){
			
		int child;
		int status;
		char input[100];
		char *cmd;
		char *cmdArr[100];
		char *execArr[100];
		char *token;
		char *savedcmd;
		int count = 0; 
		int execCount = 1;
		char *delim = " \t\r\n\f\v";
/*        int child;
        char * cmd = malloc(sizeof(char)+1);
        char * savedcmd = malloc(sizeof(char)+1);
        char * delim = malloc(sizeof(char)+1);
        char * prev = malloc(sizeof(char)+1);
        char * token = malloc(sizeof(char)+1);

		char input[100];
		char *cmd;
		char *cmdArr[100];
		char *token;
		char *savedcmd;
		int count = 0; 

        char *delim = " \t\r\n\f\v";*/
    //    prev = NULL;
		if(argc == 2){
			fgets(input, sizeof(input), (FILE*)bf);
//			printf("%s", input);
			write(STDOUT_FILENO, input, strlen(input));
		}
		else{
        	printf("mysh> ");
        	fgets(input,sizeof(input), stdin);
//			printf("This is input: %s", input);
		}
//		printf("YOU TYPED: %s\n", input);
        /*strcpy(savedcmd, cmd);
        token = strtok(cmd, delim);*/
        token  = strtok_r(input, delim,&savedcmd);
		cmd = token;
		execArr[0] = token;
//		printf("THIS IS CMD: %s\n", token);
		if(token == '\0'){
				continue;
		}
		else if(strstr(token, ".py") != 0){
//			printf("PYTHON FILE DETECTED\n");
			cmd = "python";
			execArr[0] = "python";
			execArr[1] = token;
			execCount++;
		}
		while(token != NULL){
			token = strtok_r(NULL, delim, &savedcmd);	
			cmdArr[count] = token;
			execArr[execCount] = token;
			execCount++;
			count++;
//			printf("THIS IS CMDARG: %s\n", token);
		}
		
//		int i;
//		for(i = 0; cmdArr[i] != '\0'; i++){
//				printf("ELEMENT %d is %s\n", i, cmdArr[i]);
//		}

	
		if(builtinCommands(cmd)== 1){
		//	printf("builtinCommands: %d\n", builtinCommands(cmd));
			callBuiltIns(cmd,cmdArr);
		}
		else {
		//	printf("ABOUT TO FORK.\n");
			child = fork();
			if(child == 0){
					//child process
				if(execvp(cmd, execArr) < 0){
						write(STDERR_FILENO, error_message, strlen(error_message));
						//printf("EXECUTION OF '%s' HAS FAILED OR IS AN INVALID COMMAND.\n", cmd);
						exit(1);
				}
			}
			else if(child < 0){
				printf("CHILD PROCESS FAILED.\n");
				exit(1);
			}
			else{
				while(wait(&status) != child);
			}

		}	




 
        
        




/*        while(token != NULL){

            fprintf(stderr, "THIS IS THE PREV TOKEN: %s\n", prev);
            printf("This is the current: %s\n", token);

            if(builtinCommands(token)){
               if(strcmp(prev, "cd") == 0){
                  callCdPath(token);
               }
               else{

                   callBuiltIns(token);
               }    
            }    

            strcpy(prev, token);
            
                
            //Get next token
            token = strtok(NULL, delim);
            
        }*/

    }


}
