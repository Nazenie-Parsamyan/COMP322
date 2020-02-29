#include <stdio.h> 
#include <time.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/times.h>

void PrintResult(int child, int childwait, int status)
    if(child < 0)
    {
        printf("Forking failed\n");
    }

    else if(child == 0)
    {
        printf("PPID: %d, PID: %d\n", getppid(), getpid());
    }


/*
if(pid < 0)
{
	//forking failed
	//exit(EXIT_FAILURE)
}

else if(pid == 0)
{
	//do child stuff like print its pid and ppid
	//exit(EXIT_SUCCESS)
}

else
{
	//this is where waitpid would be used
	//do parent stuff like print pid and ppid
}
*/
