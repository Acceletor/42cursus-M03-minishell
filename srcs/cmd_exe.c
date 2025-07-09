/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:54:33 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/09 22:57:41 by ksuebtha         ###   ########.fr       */
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
	if (!cmd->argv || !cmd->argv[0])
		exit (0);
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

void	init_exec_ctx(t_exec_ctx *ctx, int total)
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

	cmd = msh->cmds;
	while (cmd)
	{
		if (heredoc_prepare(cmd))
			return ;
		cmd = cmd->next;
	}
	cmd = msh->cmds;
	init_exec_ctx(&ctx, count_commands(cmd));
	if (handle_single_builtin(cmd, msh))
		return ;
	exec_loop(msh, cmd, &ctx);
	wait_all(&msh->exit_status);
}
