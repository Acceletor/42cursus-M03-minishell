#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "../libft/libft.h"
#include "../libft/get_next_line.h"

// define constants

// define structs 
typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_msh
{
    t_env *dict_env;  
} t_msh;


// function prototypes
char	*ft_strndup(const char *s1, int len);
t_env *create_env_node(const char *key, const char *value);
void add_env_node(t_env **head, const char *key, const char *value);
t_env *init_env(char **envp);
void free_env_list(t_env **head);
void print_env_list(t_env *head);

#endif