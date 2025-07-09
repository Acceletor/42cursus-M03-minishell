/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:55:00 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/07/09 22:59:01 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_external(t_command *cmd, t_msh *shell)
{
	char		*path;
	char		**envp;
	struct stat	st;

	if (!cmd->argv || !cmd->argv[0])
		exit(127);
	path = resolve_cmd_path(cmd, shell);
	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_printf("minishell: %s: is a directory\n", path);
			free(path);
			exit(126);
		}
	}
	envp = env_to_array(shell->dict_env);
	if (!envp)
		return (free(path), 1);
	execve(path, cmd->argv, envp);
	perror("execve");
	free(path);
	free_array(envp);
	exit(126);
}

int	handle_single_builtin(t_command *cmd, t_msh *msh)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!cmd || count_commands(cmd) != 1)
		return (0);
	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (!is_builtin(cmd->argv[0]))
		return (0);
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	handle_redirections(cmd->redirects);
	msh->exit_status = execute_builtins(cmd, msh);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (1);
}

void	exec_loop(t_msh *msh, t_command *cmd, t_exec_ctx *ctx)
{
	pid_t	pid;

	while (ctx->index < ctx->total)
	{
		create_pipe_if_needed(ctx->index, ctx->total, ctx->next_pipe, msh);
		pid = fork();
		if (pid == 0)
			child_process(cmd, msh, ctx);
		else if (pid < 0)
		{
			perror("minishell: fork");
			msh->exit_status = 1;
			return ;
		}
		parent_pipe_cleanup(ctx);
		cmd = cmd->next;
		ctx->index++;
	}
}
