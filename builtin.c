#include "MY_SHELL.h"
#include <stdlib.h>

extern t_history g_history;

int cell_exit(char **args)
{
    (void)args;
    dbzSpinnerLoading();
    exit(EXIT_SUCCESS);
}

int cell_env(char **args)
{
    extern char **environ;

    (void)args;
    if (!environ)
        return (1);
    for (int i = 0; environ[i]; i++)
        p("%s\n", environ[i]);
    return (0);
}

int cell_cd(char **args)
{
    if (!args[1])
    {
        p(RED "cd: missing argument\n" RST);
        return (1);
    }
    if (chdir(args[1]) != 0)
    {
        perror(RED "cd failed" RST);
        return (1);
    }
    return (0);
}

int cell_history(char **args)
{
    (void)args;
    if (g_history.count == 0)
    {
        p(Y "No commands in history\n" RST);
        return (0);
    }
    for (int i = 0; i < g_history.count; i++)
        p("%d: %s\n", i + 1, g_history.commands[i]);
    return (0);
}

int cell_mkdir(char **args)
{
    if (!args[1])
    {
        p(RED "mkdir: missing argument\n" RST);
        return (1);
    }
    if (mkdir(args[1], 0755) != 0)
    {
        perror(RED "mkdir failed" RST);
        return (1);
    }
    p(G "Directory '%s' created\n" RST, args[1]);
    return (0);
}