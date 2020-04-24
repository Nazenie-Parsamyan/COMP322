#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

static char* sigs[] = {
                       "HUP", "INT", "QUIT", "ILL", "TRAP", 
                       "ABRT", "BUS", "FPE", "USR1",
                       "SEGV", "USR2", "PIPE", "ALRM", "TERM",
                       "STKFLT", "CHLD", "CONT", "TSTP",
                       "TTIN", "TTOU", "URG", "XCPU", "XFSZ",
                       "VTALRM", "PROF", "WINCH", "IO"
                      };  
int total = 27;
int signaltermcount = 0;
int signalcount = 0;

/* signal(2) */
void sighandler(int sig) 
{
    if(sig == SIGTERM)
    {
        signaltermcount++;
    }
    else 
    {
        signaltermcount = 0;
    }
    signalcount++;

/* time(2) */
printf("SIG%s caught at %ld\n", sigs[sig-1], time(NULL));
}

/* process command-line arguments */

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Invalid # of Arguments\n");
    }


    for(int i = 1; i < argc; i++) 
    {
        for(int j = 0; j < total; j++)
        {
            /* "'strcmp' function compares argv values to a string of your choice" */
            if(strcmp(sigs[j], argv[i]) == 0 )
            {
                signal(j + 1, sighandler);
                break;
            }
        }
    }
    /* program emits a status line that includes its PID to stderr */
    fprintf(stderr, "catcher: $$ = %d\n", getpid());

    /* pause(2) */
    /* pauses continually */
    do
    {
        pause();
    } while (!(signaltermcount > 3));

    /* emits final status messade that indicates total # of signals that have been caught */
    fprintf(stderr, "catcher: Total signals count = %d\n", signalcount);
    
}   

    