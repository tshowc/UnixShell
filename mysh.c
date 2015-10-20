#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>


/*typedef struct ll_node{
    struct ll_node *next;
    char *token;
}ll_node;

typedef struct ll{
    struct ll_node *head;
    int count;
}ll;   


//DOUBLY LINKED LIST FUNCTIONS: add(), retrieve()


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
/*        char * cmd = malloc(sizeof(char)+1);
        char * savedcmd = malloc(sizeof(char)+1);
        char * delim = malloc(sizeof(char)+1);
        char * prev = malloc(sizeof(char)+1);
        char * token = malloc(sizeof(char)+1);*/

		char cmd[100];
		char *cmdArr[100];

//        delim = " \t\r\n\f\v";
    //    prev = NULL;

        printf("mysh> ");
        fgets(cmd,sizeof(cmd), stdin);
		printf("YOU TYPED: %s\n", cmd);
        /*strcpy(savedcmd, cmd);
        token = strtok(cmd, delim);*/
      //  token = strtok_r(cmd, delim, &savedcmd);
        
 
        
        




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
