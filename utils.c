#include "MY_SHELL.h"
#include <unistd.h>
#include <sysexits.h>

void Getcwd(char *buf, size_t size)
{
    if (NULL == getcwd(buf, size))
        perror(RED "getcwd FAILED" RST);
    p("[DEBUG] Getcwd appelée\n");
}

void *Malloc(size_t size)
{
    void *ptr;
    if (size == 0)
        return (NULL);
    ptr = malloc(size);
    if (!ptr)
    {
        perror(RED "Malloc failed" RST);
        exit(EXIT_FAILURE);
    }
    return (ptr);
}

pid_t Fork(void)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror(RED "Fork failed" RST);
        exit(EX_OSERR);
    }
    return (pid);
}

void Execvp(const char *file, char *const argv[])
{
    if (!file || !argv)
    {
        fprintf(stderr, RED "Execvp: invalid arguments \n" RST);
        exit(EXIT_FAILURE);
    }
    if (execvp(file, argv) == -1)
    {
        perror(RED " CELL_jR failed" RST);
        exit(EX_UNAVAILABLE);
    }
}

pid_t Wait(int *status)
{
    pid_t result;
    if (!status)
    {
        fprintf(stderr, RED "wait: status argument required\n" RST);
        return -1;
    }

    result = wait(status);
    if (result == -1)
        perror(RED "wait failed" RST);
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    return result;
}

void *Realloc(void *ptr, size_t size)
{
    void *new_ptr;

    if (size == 0)
        return NULL;

    new_ptr = realloc(ptr, size);
    if (!new_ptr)
    {
        perror(RED "Realloc failed" RST);
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

void dbzSpinnerLoading()
{
    const char *charging[] = {
        "[]",
        "[=           ]",
        "[==          ]",
        "[===         ]",
        "[====        ]",
        "[=====       ]",
        "[======      ]",
        "[=======     ]",
        "[========    ]",
        "[=========   ]",
        "[==========  ]",
        "[=========== ]",
        "[=========== 👑]",
    };
    const int frames = sizeof(charging) / sizeof(charging[0]);
    p(RED "Shutting down...\n" RST);

    for (int i = 0; i < frames; i++) {
        p("\r" Y "%s" RST, charging[i]);
        fflush(stdout);
        usleep(421337);
    }
    p(C "\n ✅ EXIT ✅ \n" RST);
    exit(EXIT_SUCCESS);
}

void printbanner(void)
{
    p(G "▗▖  ▗▖▗▖  ▗▖▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖       ▗▖  ▗▖█\n" 
        "▐▛▚▞▜▌ ▝▚▞▘▐▌   ▐▌ ▐▌▐▌   ▐▌   ▐▌       ▐▌  ▐▌█\n" 
        "▐▌  ▐▌  ▐▌  ▝▀▚▖▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌       ▐▌  ▐▌█\n"
        "▐▌  ▐▌  ▐▌ ▗▄▄▞▘▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖     ▝▚▞▘ █\n" RST);
}