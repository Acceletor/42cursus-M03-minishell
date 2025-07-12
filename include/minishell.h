/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:20:48 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/07/12 22:18:01 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>

// define constants
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_UNKNOWN
}						t_token_type;

// define structs
typedef struct s_builtin
{
	char				*input;
	char				**args;
	int					argc;
	int					status_exit;
}						t_builtin;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_command
{
	char				**argv;
	t_redirect			*redirects;
	int					status_exit;
	int					argc;
	struct s_command	*next;
}						t_command;

typedef struct s_msh
{
	t_env				*dict_env;
	char				*input;
	t_token				*tokens;
	t_command			*cmds;
	int					exit_status;
}						t_msh;

typedef struct s_exec_ctx
{
	int					index;
	int					total;
	int					prev_pipe[2];
	int					next_pipe[2];
}						t_exec_ctx;

// function prototypes

// main.c
void					print_welcome_message(void);
int						check_input_and_exit(char *input);
void					free_msh(t_msh *msh, int exit_code);

// env_util.c
t_env					*create_env_node(const char *key, const char *value);
void					add_env_node(t_env **head, const char *key,
							const char *value);
t_env					*init_env(char **envp);
void					free_env_list(t_env **head);
void					print_env_list(t_env *head);

// token.c
t_token					*token_stream(t_msh *msh);
int						skip_whitespace(char *input, int *i);
char					*extract_word_part(t_msh *msh, int *i);
int						handle_word(t_msh *msh, int *i, t_token **tokens);

// token_special.c
int						handle_pipe(char *input, int *i, t_token **tokens);
int						handle_redir_out(char *input, int *i, t_token **tokens);
int						handle_redir_in(char *input, int *i, t_token **tokens);
int						handle_special_tokens(char *input, int *i,
							t_token **tokens);
void					add_token_by_type(char *chunk, t_token **tokens);

// token_util.c
t_token					*new_token(char *value, t_token_type type);
void					add_token(t_token **head, t_token *new);
void					print_tokens(t_token *tokens);
void					free_tokens(t_token **tokens);

// token_word.c
char					*extract_single_quote(char *input, int *i);
char					*extract_double_quote(char *input, int *i, t_msh *msh);
char					*extract_plain_text(char *input, int *i);

// token_word_util.c
char					*extract_var_name(const char *str, int *i);
char					*get_variable_value(char *var, t_msh *msh);
char					*strjoin_and_free(char *s1, char *s2);
char					*handle_dollar_braces(char *input, int *i);
char					*extract_dollar_value(char *input, int *i, t_msh *msh);

// parser.c
t_command				*init_command(void);
void					add_command(t_command **cmds, t_command *new);
void					add_argument(t_command *cmd, char *value);
void					add_redirect(t_command *cmd, t_token **tokens);
t_command				*parser(t_token *tokens);

// parser_util.c
void					print_redirects(t_redirect *redir);
void					print_command_list(t_command *cmds);
void					free_redirects(t_redirect *redir);
void					free_command_list(t_command *cmds);

// syntax_checker.c
int						check_pipe_syntax(t_token *tokens);
int						check_redirect_syntax(t_token *tokens);

// redirections.c
int						handle_single_redirect(t_redirect *redir,
							t_redirect *last_heredoc);
void					handle_redirections(t_command *cmd, t_msh *msh);
int						handle_heredoc(const char *delimiter);
int						heredoc_prepare(t_command *cmd);

/*     cmd_exe.c         */
void					child_process(t_command *cmd, t_msh *msh,
							t_exec_ctx *ctx);
void					parent_pipe_cleanup(t_exec_ctx *ctx);
void					wait_all(int *exit_status);
void					init_exec_ctx(t_exec_ctx *ctx, int total);
void					execute(t_msh *msh);

//  cmd_exe_utils.c    
int						is_builtin(char *cmd);
int						execute_builtins(t_command *cmd, t_msh *shell);
int						count_commands(t_command *cmd);
int						create_pipe_if_needed(int i, int total, int pipefd[2],
							t_msh *msh);
char					*resolve_cmd_path(t_command *cmd, t_msh *shell);

//	cmd_exe_utils2.c 
int						exec_external(t_command *cmd, t_msh *shell);
int						handle_single_builtin(t_command *cmd, t_msh *msh);
void					exec_loop(t_msh *msh, t_command *cmd, t_exec_ctx *ctx);

/*     exec_utils.c      */
char					*strjoin_three_and_free(char *s1, char *s2, char *s3);
void					free_array(char **arr);
char					*get_path_name(t_command *cmd, t_env *env);
char					*join_key_value(char *key, char *value);
char					**env_to_array(t_env *env_list);

/*      builtins         */
int						ft_echo(t_command *cmd);
int						ft_cd(t_command *cmd, t_msh *shell);
int						ft_pwd(t_command *cmd);
int						ft_export(t_command *cmd, t_env **env_list);
int						ft_unset(t_command *cmd, t_env **env_list);
int						ft_env(t_command *cmd, t_env *env_list);
int						ft_exit(t_msh *msh);

// ft_export_util.c
void					print_export_list(t_env *env_list);

/*      env_util         */
t_env					*create_env_node(const char *key, const char *value);
void					add_env_node(t_env **head, const char *key,
							const char *value);
t_env					*init_env(char **envp);
void					free_env_list(t_env **head);
void					print_env_list(t_env *head);

/*      env_util2         */
char					*get_env_value(t_env *env, char *key);
void					set_env_value(t_env **head, const char *key,
							const char *value);
void					remove_env_key(t_env **head, const char *key);
bool					env_exists(t_env *env_list, const char *key);

/*      signals           */
void					handle_sigquit(int sig);
void					handle_sigint(int sig);
void					setup_signals(void);

#endif