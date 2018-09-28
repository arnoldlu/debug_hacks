#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
 
#define SIZE 1000

void trace(int signo)
{
    int j, nptrs;

    void *buffer[SIZE];
    char **strings;
 
    printf("signo: %d\n", signo);

    nptrs = backtrace(buffer, SIZE);
    printf("backtrace() returned %d addresses\n", nptrs);

    /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
     *               would produce similar output to the following: */

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("Backtrace:");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < nptrs; j++)
        printf("%s\n", strings[j]);

    free(strings);

    if (SIGSEGV == signo || SIGQUIT == signo) {
        exit(0);
    }
}
 
void segfault(void)
{
    int *p = NULL;
    *p = 1;
}
 
int main(int argc, char *argv[])
{
    signal(SIGSEGV, trace);
    signal(SIGINT, trace);
    signal(SIGQUIT, trace);

    while (1) {
        sleep(1);
        if (time(0) % 7 == 0) {
            segfault();
        }
    }

    return 0;
}
