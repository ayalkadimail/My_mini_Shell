#include "MY_SHELL.h"
#include <stdio.h>

t_history g_history = {{0}, 0};

t_builtin g_builtin[] =
{
    {.builtin_name="env", .foo=cell_env},
    {.builtin_name="exit", .foo=cell_exit},
    {.builtin_name="cd", .foo=cell_cd},
    {.builtin_name="history", .foo=cell_history},
    {.builtin_name="mkdir", .foo=cell_mkdir},
    {.builtin_name=NULL, .foo=NULL},
};

int status = 0;

void cell_launch(char **args)
{
    int fd_in = -1, fd_out = -1;
    char *input_file = NULL, *output_file = NULL;
    int i = 0;

    // Check for redirection operators
    while (args[i])
    {
        if (strcmp(args[i], ">") == 0 && args[i + 1])
        {
            output_file = args[i + 1];
            args[i] = NULL; // Terminate args at '>'
            break;
        }
        else if (strcmp(args[i], "<") == 0 && args[i + 1])
        {
            input_file = args[i + 1];
            args[i] = NULL; // Terminate args at '<'
            break;
        }
        i++;
    }

    pid_t pid = Fork();
    if (pid == CELL_Jr)
    {
        // Handle output redirection
        if (output_file)
        {
            fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0)
            {
                perror(RED "output redirection failed" RST);
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        // Handle input redirection
        if (input_file)
        {
            fd_in = open(input_file, O_RDONLY);
            if (fd_in < 0)
            {
                perror(RED "input redirection failed" RST);
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        Execvp(args[0], args);
    }
    else
    {
        Wait(&status);
    }
}

void cell_exec(char **args)
{
    int i;
    const char *curr;

    if (!args[0])
        return;

    i = 0;
    while ((curr = g_builtin[i].builtin_name))
    {
        if (!strcmp(curr, args[0]))
        {
            status = g_builtin[i].foo(args);
            return;
        }
        i++;
    }

    cell_launch(args);
}

char **cell_split_line(char *line)
{
    char **tokens;
    unsigned int position;
    size_t bufsize;

    bufsize = BUFSIZ;
    tokens = Malloc(bufsize * sizeof *tokens);
    position = 0;

    for (char *token = strtok(line, DEL); token; token = strtok(NULL, DEL))
    {    
        tokens[position++] = token;
        if (position >= bufsize)
        {
            bufsize *= 2;
            tokens = Realloc(tokens, bufsize * sizeof(*tokens));
        }
    }
    tokens[position] = NULL;
    return tokens;
}

char *cell_read_line(void)
{
    char *buf = NULL;
    size_t bufsize = 0;
    char cwd[BUFSIZ];

    Getcwd(cwd, sizeof(cwd));

    p(C "👾 %s 👾" RST "$> ", cwd);  // prompt

    if (getline(&buf, &bufsize, stdin) == -1) 
    {
        free(buf);
        buf = NULL;
        if (feof(stdin))
            p(RED "[EOF]\n" RST);
        else
            p(RED "Getline failed\n" RST);
    }
    else if (buf && buf[0] != '\n')
    {
        // Store in history
        if (g_history.count < MAX_HISTORY)
        {
            g_history.commands[g_history.count] = strdup(buf);
            g_history.count++;
        }
        else
        {
            free(g_history.commands[0]);
            for (int i = 1; i < MAX_HISTORY; i++)
                g_history.commands[i - 1] = g_history.commands[i];
            g_history.commands[MAX_HISTORY - 1] = strdup(buf);
        }
    }

    return buf;
}

int main()
{
    char *line;
    char **args;

    printbanner();

    while ((line = cell_read_line()))
    {
        args = cell_split_line(line);
        cell_exec(args);

        free(line);
        free(args);
    }

    // Free history
    for (int i = 0; i < g_history.count; i++)
        free(g_history.commands[i]);

    return EXIT_SUCCESS;
}