//stacknode for storing command tokens from strtok
typedef struct{
    char * command;
    int count;
    struct stacknode * next;
}stacknode;

