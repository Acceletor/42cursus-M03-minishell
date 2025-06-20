/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:20:48 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/20 23:09:16 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include "readline/readline.h"
# include "readline/history.h"

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf.h"


// define constants
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT, // >
	TOKEN_REDIR_IN, // <
	TOKEN_APPEND, // >>
	TOKEN_HEREDOC, // <<
	TOKEN_UNKNOWN
}	t_token_type;

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
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	t_token_type	type; // from enum 
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	int					type; // REDIRECT_OUT, REDIRECT_IN, REDIRECT_APPEND..
	char				*file; //out.txt
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char				**argv; // ["cat", "file.txt", NULL]
	t_redirect			*redirects; //linked list of redirection 
	struct s_command	*next;
}	t_command;

typedef struct s_msh
{
	t_env		*dict_env; // listed list of env
	char		*input; //raw input from readline()
	t_token		*tokens;
	t_command	*cmds;
	int			last_exit_code;
}	t_msh;

// function prototypes

// env_util.c
t_env		*create_env_node(const char *key, const char *value);
void		add_env_node(t_env **head, const char *key, const char *value);
t_env		*init_env(char **envp);
void		free_env_list(t_env **head);
void		print_env_list(t_env *head);

// token.c
char		*get_env_value(t_env *env, char *key);
t_token		*token_stream(char *input, t_env *env);

// token_special.c
int			handle_pipe(char *input, int *i, t_token **tokens);
int			handle_redir_out(char *input, int *i, t_token **tokens);
int			handle_redir_in(char *input, int *i, t_token **tokens);
int			handle_special_tokens(char *input, int *i, t_token **tokens);
void		handle_word(char *input, int *i, t_token **tokens);

// token_util.c
t_token		*new_token(char *value, t_token_type type);
void		add_token(t_token **head, t_token *new);
void		print_tokens(t_token *tokens);
void		free_tokens(t_token **tokens);

// token_quote.c
char		*extract_var_name(const char *str, int *i);
char		*append_var_val(char *result, const char *str, int *i, t_env *env);
char		*append_char(char *result, const char *str, int *i);
char		*expand_dollar_variable(char *str, t_env *env);
int			handle_quotes(char *input, int *i, t_token **tokens, t_env *env);

// parser.c
t_command	*init_command(void);
void		add_command(t_command **cmds, t_command *new);
void		add_argument(t_command *cmd, char *value);
void		add_redirect(t_command *cmd, t_token **tokens);
t_command	*parser(t_token *tokens);

// parser_util.c
void		print_redirects(t_redirect *redir);
void		print_command_list(t_command *cmds);
void		free_redirects(t_redirect *redir);
void		free_command_list(t_command *cmds);

// syntax_checker.c
int			check_pipe_syntax(t_token *tokens);


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
void set_env_value(t_env **head, const char *key, const char *value);
void remove_env_key(t_env **head, const char *key);
int execute_builtins(t_builtin *cmd, t_msh *shell);
#endif