/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:54:33 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/08 18:35:52 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_command *cmd, t_msh *msh, t_exec_ctx *ctx)
{
	if (ctx->index > 0)
	{
		dup2(ctx->prev_pipe[0], STDIN_FILENO);
		close(ctx->prev_pipe[0]);
	}
	if (ctx->index < ctx->total - 1)
	{
		close(ctx->next_pipe[0]);
		dup2(ctx->next_pipe[1], STDOUT_FILENO);
		close(ctx->next_pipe[1]);
	}
	handle_redirections(cmd->redirects);
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtins(cmd, msh));
	if (exec_program_name(cmd, msh) == 0)
		exit(0);
	exec_external(cmd, msh);
	exit(1);
}

void	parent_pipe_cleanup(t_exec_ctx *ctx)
{
	if (ctx->index > 0)
		close(ctx->prev_pipe[0]);
	if (ctx->index < ctx->total - 1)
	{
		ctx->prev_pipe[0] = ctx->next_pipe[0];
		ctx->prev_pipe[1] = ctx->next_pipe[1];
		close(ctx->next_pipe[1]);
	}
}

void	wait_all(int *exit_status)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			*exit_status = WEXITSTATUS(status);
	}
}

static void	init_exec_ctx(t_exec_ctx *ctx, int total)
{
	ctx->index = 0;
	ctx->total = total;
	ctx->prev_pipe[0] = -1;
	ctx->prev_pipe[1] = -1;
	ctx->next_pipe[0] = -1;
	ctx->next_pipe[1] = -1;
}

void	execute(t_msh *msh)
{
	t_command	*cmd;
	t_exec_ctx	ctx;
	pid_t		pid;
	int			stdin_backup;
	int			stdout_backup;

	cmd = msh->cmds;
	init_exec_ctx(&ctx, count_commands(cmd));
	if (ctx.total == 1 && is_builtin(cmd->argv[0]))
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		handle_redirections(cmd->redirects);
		msh->exit_status = execute_builtins(cmd, msh);
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
		return ;
	}
	while (ctx.index < ctx.total)
	{
		create_pipe_if_needed(ctx.index, ctx.total, ctx.next_pipe, msh);
		pid = fork();
		if (pid == 0)
			child_process(cmd, msh, &ctx);
		else if (pid < 0)
		{
			perror("minishill: fork");
			msh->exit_status = 1;
			return ;
		}
		parent_pipe_cleanup(&ctx);
		cmd = cmd->next;
		ctx.index++;
	}
	wait_all(&msh->exit_status);
}
