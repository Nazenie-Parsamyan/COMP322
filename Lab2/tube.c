#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    pid_t child1; 
    int status1;
    
    pid_t child2;
    int status2;

    char* newargv1[argc];  
    char* newargv2[argc];

    int pipefd[2]; 

     if(argc<=1)
     {
        fprintf(stderr,"Error: Not enough arguements.\n");
        exit(EXIT_FAILURE);
     }

    int i;
    
    for(i = 1; i < argc; i++)
    {
      if(strcmp(argv[i], ",")==0)
      {
        break;
      }
        newargv1[i-1]=argv[i];
    }
    
    newargv1[i] = (char*)0;

    if(i+1 >= argc)
    {
        fprintf(stderr,"Error:Not enough arguements.\n");
        exit(EXIT_FAILURE);
    }
    
    int j;
    
    for(j=1; j+i < argc; j++)
    {
        newargv2[j-1]=argv[i+j];
    }
    newargv2[i] = (char*)0;

    if (pipe(pipefd) == -1)
    {
        fprintf(stderr,"Error:Pipe Failed\n");
        exit(EXIT_FAILURE);
    }

    
    child1 = fork();

    if (child1>0)
    {
       child2 = fork();

       if(child2<0)
       {
         fprintf(stderr,"Error:Fork Failed\n");
         exit(EXIT_FAILURE); 
       }
       
       else if(child2>0)
       {
         close(pipefd[1]);
         
         fprintf(stderr, "child 1 %s: $$ = %d\n", newargv1[0], getpid());
		   fprintf(stderr, "child 2 %s: $$ = %d\n", newargv2[0], getpid());

		   waitpid(child1, &status1, WUNTRACED);

		   fprintf(stderr, "child 1 %s: $? = %d\n", newargv1[0], status1);

		   waitpid(child2, &status2, WUNTRACED);
         
		   fprintf(stderr, "child 2 %s: $? = %d\n", newargv2[0], status2);
        }
        
        else
        {
          close(pipefd[1]);
          dup2(pipefd[0],0);
          close(pipefd[0]);
          execve(newargv1[0], newargv2, NULL);
        }

    }
    
    else if(child1 < 0)
    {
        fprintf(stderr,"Error:Fork Failed\n");
        exit(EXIT_FAILURE);   
    }
    
    else
    {
        close(pipefd[0]);
        dup2(pipefd[1],1);
        close(pipefd[1]);

        execve(newargv2[0], newargv1, NULL);
    }
    
    return 0;
}
