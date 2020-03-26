#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void PrintResult() 
{
    
}

int main(int argc, char** argv)
{
   if(argc <= 1)
   {
        fprintf(stderr,"Error: Not enough arguements.\n");
        exit(EXIT_FAILURE);
   }

    pid_t child;
    child = fork();

    if (child < 0)
    {
       fprintf(stderr,"FORK FAILED\n");
       exit(EXIT_FAILURE);
    }
    
    else if(child == 0)
    {
        char *newargv[argc-1];
        int i;
        
        for(i=1; i < argc; i++)
        {

           newargv[i-1] = argv[i];
           printf("%s\n", newargv[i]);
        }
         execve(argv[1], newargv, NULL);
         perror("execve");   
         exit(EXIT_FAILURE);   
    }

    else
    {
        int status;
        
        fprintf(stderr, "%s: $$ = %d\n", argv[1], child);
        waitpid(child, &status,WUNTRACED);
        fprintf(stderr, "%s: $? = %d\n", argv[1], status);
    }
    exit(EXIT_FAILURE);

}
