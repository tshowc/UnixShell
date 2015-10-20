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
 const char* home = getenv("HOME");
 if(chdir(home) == 0){
     printf("Directory is now %s\n", home);
     return EXIT_SUCCESS;

 }
 else{
     printf("File directory %s not found.\n", home); 
     return EXIT_FAILURE;
 }

}

int callCdPath(char *path)
{
    if(chdir(path) == 0){
        printf("Directory is now ");
        callPwd();
        return EXIT_SUCCESS;
    }
    else{
        printf("File directory %s not found.\n", path); 
        return EXIT_FAILURE; 
    }   
}    



int callWait()
{

}    


int main(int argc, char *argv[])
{
    while(1){
        int child;
        char * cmd = malloc(sizeof(char)+1);
        char * savedcmd = malloc(sizeof(char)+1);
        char * delim = malloc(sizeof(char)+1);
        char * prev = malloc(sizeof(char)+1);
        char * token = malloc(sizeof(char)+1);

        delim = " \t\r\n\f\v";
    //    prev = NULL;

        printf("mysh> ");
        gets(cmd);
        strcpy(savedcmd, cmd);
        token = strtok(cmd, delim);
        
        
        while(token != NULL){

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
            
        }

    }


}
