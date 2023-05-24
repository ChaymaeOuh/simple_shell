#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>


#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define MAX_WORD_COUNT 100
#define NEG_ONE -1
#define REG_FLAG 0
#define OR_FLAG 1
#define AND_FLAG 2
#define CHAIN_FLAG 3
#define BAS_CHANGE_LOWER 1
#define BAS_CHANGE_UNSIG 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE_NAME "history"
#define HIST_SIZE_MAX 4096
#define SET_INFO \
{NULL, 0, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

extern char **environ;

/**
 * struct NodeList - singly linked lidt
 * @num: the number field
 * @str: string
 * @next: pointer to the next node
 */
typedef struct NodeList
{
int num;
char *str;
struct NodeList *next;
} list_f;

/**
 * struct NodeInfo - contains simulated arguments for a function pointer
 * @arg: a string generated from getline
 * @argc: number of arguments
 * @argv: array of arguments
 * @path: path string for the current command
 * @lines: number of errors encountred
 * @error_code: the exit error code
 * @lc_flag: flag indecating when an inout line should be counted
 * @prog_name: name of program's file
 * @env: linked list of environment variables
 * @environ: a custom-modified copy of the environ
 * @history: node for the command history
 * @alias: node for command alias
 * @env_changed: flag endicating environ changed
 * @status: return status of executed commands
 * @sep_buff: pointer of sep_buff
 * @sep_buff_kind: type of comand buff
 * @fd_read: file descriptor used for reading input
 * @hist_lines: number of lines in history
 */
typedef struct NodeInfo
{
char *arg;
int argc;
char **argv;
char *path;
size_t lines;
int error_code;
int lc_flag;
char *prog_name;
list_f *env;
list_f *history;
list_f *alias;
char **environ;
int env_changed;
int status;
char **sep_buff;
int sep_buff_kind;
int fd_read;
int hist_lines;
} info_f;

/**
 * struct builtin - contains a builtin string
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
char *type;
int (*func)(info_f *);
} builtin_cmds;




int my_shell(info_f *info, char **av);
int my_write_char(char c, int fd);
int my_write_chars(char *str, int fd);
int my_strlen(char *s);
int my_strcmp(char *s1, char *s2);
int my_putchar(char);
int my_putchar_err(char);
int my_isalpha(int);
int my_atoi(char *);
int my_err_num(char *);
int my_exit(info_f *);
int my_cd(info_f *);
int my_help(info_f *);
int my_history(info_f *);
int my_alias(info_f *);
int my_getline(info_f *, char **, size_t *);
int my_printenv(info_f *);
int my_check_setenv(info_f *);
int my_check_unsetenv(info_f *);
int my_setenv(info_f *, char *, char *);
int my_unsetenv(info_f *, char *);
void my_puts(char *);
void my_puts_err(char *);
char *my_strcat(char *, char *);
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);
char *my_memset(char *, char, unsigned int);
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *my_getenv(info_f *, const char *);
char *my_starts_with(const char *, const char *);
char *my_dup_chars(char *, int, int);
char *my_check_file_in_path(info_f *info, char *pathstr, char *cmd);
char *my_change_base(long int, int, int);
char *my_read_hist(info_f *info);
char **my_get_environ(info_f *);
char **my_strtow(char *, char *);
char **my_list_to_vector(list_f *);
void my_check_command(info_f *);
void my_create_process(info_f *);
void my_sigint(int);
void my_clear_info(info_f *);
void my_set_info(info_f *, char **);
void my_free_info(info_f *, int);
void my_free_vector(char **);
void my_print_error(info_f *, char *);
void my_comments(char *);
void my_free_list(list_f **);
void my_check_chain(info_f *info, char *buf, size_t *p, size_t i, size_t len);
int my_builtin(info_f *);
bool my_is_executable(info_f *, char *);
int my_loophsh(char **);
int my_bfree(void **);
int my_from_terminal(info_f *);
int my_print_dec(int, int);
int my_gather_env(info_f *);
int my_create_history(info_f *info);
int my_read_history(info_f *info);
int my_update_history(info_f *info, char *buf, int linecount);
int my_renumber_history(info_f *info);
int my_delete_node_at_index(list_f **, unsigned int);
bool my_is_chain(info_f *, char *, size_t *);
int my_change_alias(info_f *);
int my_change_v(info_f *);
int my_change_string(char **, char *);
list_f *my_add_node_start(list_f **head, const char *str, int num);
list_f *my_add_node_end(list_f **head, const char *str, int num);
list_f *my_node_str_start(list_f *, char *, char);
size_t my_print_list_str(const list_f *);
size_t my_listlen(const list_f *);
size_t my_print_list(const list_f *);
ssize_t my_get_input(info_f *);
ssize_t my_node_index(list_f *, list_f *);
char **my_split_string(char *str, char *separators, size_t *word_count);
int my_words_count(char *str, char *separators, unsigned int *arr);
void my_set_zeros(unsigned int *arr, size_t size);
void my_set_nulls(char *arr, size_t size);
bool my_is_delimiter(char c, char *delimiters);

#endif /*SHELL_H */

