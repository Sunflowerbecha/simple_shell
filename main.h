#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
* struct list_s - A new struct type defining a linked list.
* @dir: A directory path.
* @next: A pointer to another struct list_s.
*/
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
* struct builtin_s - A new struct type defining builtin commands.
* @name: The name of the builtin command.
* @f: A function pointer to the builtin command's function.
*/
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
* struct alias_s - A new struct defining aliases.
* @name: The name of the alias.
* @value: The value of the alias.
* @next: A pointer to another struct alias_s.
*/
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main functions */
ssize_t _getline(char **lptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lptr, size_t *n, char *buff, size_t b);
char **_strtok(char *line, char *delim);
char *get_location(char *cmds);
list_t *get_path_dir(char *dir_list);
int execute(char **args, char **front);


/* Argument Helpers */
void handle_line(char **line, ssize_t read);
void variable_replacement(char **line, int *exec_resp);
char *get_args(char *line, int *exec_resp);


int call_args(char **args, char **front, int *exec_resp);
int run_args(char **args, char **front, int *exec_resp);
int handle_args(int *exec_resp);
int check_args(char **ags);
void free_args(char **args, char **front);
char **replace_aliases(char **ags);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_itoa(int num);
int num_len(int num);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int sh_exit(char **ags, char **front);
int sh_env(char **args, char __attribute__((__unused__)) **front);
int sh_setenv(char **args, char __attribute__((__unused__)) **front);
int sh_unsetenv(char **args, char __attribute__((__unused__)) **front);
int sh_cd(char **args, char __attribute__((__unused__)) **front);
int sh_alias(char **args, char __attribute__((__unused__)) **front);
int sh_help(char **args, char __attribute__((__unused__)) **front);

/* env_handlers */
char **_duplicateEnv(void);
char **_getenv(const char *var);
char *get_env_value(char *beginning, int len);

/* Error Handling */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* mem_formaters and linked_lists */
void free_env(void);
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);


/* help */
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/* file proccessor */
int run_cmd_file(char *f_path, int *exec_resp);
int cant_open(char *f_path);


/* others */
void sig_handler(int sig);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);
char *get_pid(void);
char *fill_path_dir(char *dirpath);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);



int exet_nzero(char **args, char **front, int *exec_resp, int ind);
int exet_zero(char **args, char **front, int *exec_resp, int ind);
int set_pa(char **args);
char chk_agv_val(char **args, char *o_pwd);
int try_execute(char **args, char **front, char *cmd, int flag);
void child_zero(char **args, char *cmd, char **front);
void do_path_cattt(char *dirpath, char *path_copy, char *pwd);
void logical_ops(char *line, ssize_t *new_len);
void handle_line_pttion(void);
void handle_line_pttion2(void);

#endif
