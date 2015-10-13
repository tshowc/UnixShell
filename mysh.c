#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int builtinCommands(char *c)
{

    int isBuiltIn = 0;

   if( (strcmp(c, "exit") == 0) || (strcmp(c, "pwd") == 0) || (strcmp(c, "cd")) || (strcmp(c, "wait"))){
     isBuiltIn = 1;
   }

    return isBuiltIn;  
}    


void callBuiltIns(char *c)
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
        callCd();
    }    
    else if(strcmp(c, "wait") == 0)
    {
        callWait();
    }
    else
    {
        printf("ERROR THIS IS NOT A BUILTIN COMMAND.\n");
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


int callCd()
{

}

int callWait()
{

}    


int main(int argc, char *argv[])
{
    while(1){
        int child;
        char * cmd = malloc(sizeof(char));
        char * savedcmd = malloc(sizeof(char));
        char * delim = malloc(sizeof(char));
        char *token;

        delim = " \t\r\n\f\v";


        printf("mysh> ");
        gets(cmd);
        strcpy(savedcmd, cmd);
        token = strtok(cmd, delim);

        while(token != NULL){
            printf(" %s\n", token);
            
            if(builtinCommands(token)){
               callBuiltIns(token); 
            }    

            //Get next token
            token = strtok(NULL, delim);
            
            
        }

               
    }


}
