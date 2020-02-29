#include <stdio.h> 
#include <time.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/times.h>

void PrintResult(int pid, int pid_wait, int status)
{
    if(pid < 0)
    {
        printf("Forking failed\n");
    }
    else if(pid == 0)
    {
        printf("PPID: %d, PID: %d\n", getppid(), getpid());
    }
    else 
    {
        printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d\n", getppid(), getpid(), pid_wait, status);
    }
}

int main() 
{
    time_t start;
    time_t stop;
    pid_t pid_wait;
    pid_t pid;

    clock_t clock_time;
    struct tms process_time;

    time(&start);

    printf("Start: %ld\n", start);


    pid = fork();

    if(pid < 0)
    {
        PrintResult(pid, 0, 0);
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        PrintResult(pid, 0, 0);
        exit(EXIT_SUCCESS);
    }
    else 
    {
        int status;
        pid_wait = waitpid(pid, &status, WUNTRACED);
        PrintResult(pid, pid_wait, status);
    }

        clock_time = times(&process_time);

        printf("USER: %ld, SYS: %ld\n", process_time.tms_utime, process_time.tms_stime);
        printf("CUSER: %ld, CSYS: %ld\n", process_time.tms_cutime, process_time.tms_cstime);

        stop = time(NULL);
        printf("STOP: %ld", stop);

        exit(EXIT_SUCCESS);

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
