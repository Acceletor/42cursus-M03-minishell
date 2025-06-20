#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include "../libft/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>   

// define constants

// define structs 

typedef struct s_builtin
{
	char	*input;
	char	**args;
	int argc;
	int status_exit;
}			t_builtin;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_msh
{
    t_env *dict_env;
    int last_exit_code;
} t_msh;


// function prototypes

/*      builtins         */
int ft_cd(t_builtin *cmd, t_msh *shell);
int ft_echo(t_builtin *cmd);
int	ft_env(t_builtin *cmd, t_env *env_list);
int ft_pwd(t_builtin *cmd);
int	ft_export(t_builtin *cmd, t_env **env_list);
int ft_exit(t_builtin *cmd, int last_exit_code);
int ft_unset(t_builtin *cmd, t_env **env_list);

int check_cd(t_builtin *cmd, t_msh *shell);
int get_old_pwd(t_builtin *cmd, t_msh *shell);
void update_pwd(t_msh *shell);

/*      env_util         */
t_env *create_env_node(const char *key, const char *value);
void add_env_node(t_env **head, const char *key, const char *value);
t_env *init_env(char **envp);
void free_env_list(t_env **head);
void print_env_list(t_env *head);

/*      env_util2         */
char *get_env_value(t_env *env_list, const char *key);
void set_env_value(t_env **head, const char *key, const char *value);
void remove_env_key(t_env **head, const char *key);
int execute_builtins(t_builtin *cmd, t_msh *shell);
#endif