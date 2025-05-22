#ifndef MY_SHELL_H
# define MY_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ftw.h>

#define Y       "\033[1;33m"
#define G       "\033[1;32m"
#define C       "\033[1;36m"
#define RED     "\033[1;31m"
#define RST     "\033[0m"

#define p(...) printf(__VA_ARGS__)
#define DEL "\n\t \v\f\r"
#define CELL_Jr 0
#define MAX_HISTORY 100

typedef struct s_builtin
{
    const char *builtin_name;
    int (*foo)(char **);
} t_builtin;

typedef struct s_history
{
    char *commands[MAX_HISTORY];
    int count;
} t_history;

int cell_exit(char **args);
int cell_env(char **args);
int cell_cd(char **args);
int cell_history(char **args);
int cell_mkdir(char **args);
int cell_rmdir(char **args);
int cell_ls(char **args);
int cell_rm(char **args);
int cell_pwd(char **args);
void cell_exec(char **args);
char *cell_read_line(void);
char **cell_split_line(char *line);

pid_t Fork(void);
pid_t Wait(int *status);
void Execvp(const char *file, char *const argv[]);

void dbzSpinnerLoading(void);
void Getcwd(char *, size_t);
void printbanner(void);
void *Malloc(size_t);
void *Realloc(void *ptr, size_t size);

#endif