/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:54:33 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/06 23:55:49 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    return (
        ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0
    );
}

int execute_builtins(t_command *cmd, t_msh *shell)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (1);
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return (ft_echo(cmd));
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return ft_cd(cmd, shell);
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        return ft_pwd(cmd);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        return ft_export(cmd, &shell->dict_env);
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        return ft_unset(cmd, &shell->dict_env);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        return ft_env(cmd, shell->dict_env);
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
       return (ft_exit(cmd));

    return (1);
}
// //complete it and think all cases
// static void	execve_child(char *path, t_command *cmd, char **envp)
// {
// 	execve(path, cmd->argv, envp);
// 	perror(cmd->argv[0]);
// 	exit(1);
// }

// static int	handle_fork(char *path, t_command *cmd, char **envp)
// {
// 	pid_t	pid;
// 	int		status = 0;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		return (1);
// 	}
// 	else if (pid == 0)
// 		execve_child(path, cmd, envp);
// 	else
// 		waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (1);
// }

int	exec_external(t_command *cmd, t_msh *shell)
{
	char	*path;
	char	**envp;

    if (!cmd->argv || !cmd->argv[0])
    {
        exit(127);
    }
	path = get_path_name(cmd, shell->dict_env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		exit (127);
	}
	envp = env_to_array(shell->dict_env);
	if (!envp)
		return (free(path), 1);
    execve(path, cmd->argv, envp);
    perror("execve");
	// result = handle_fork(path, cmd, envp);
	free(path);
	free_array(envp);
	exit(126);
}

// void execute(t_msh *msh)
// {
//     t_command *cmd;
    
//     cmd = msh->cmds;
//     while(cmd)
//     {
//         if (is_builtin(cmd->argv[0]))
//             msh->exit_status = execute_builtins(cmd, msh);
//         else
//             //print_command_list(cmd);
//             msh->exit_status = exec_external(cmd, msh);
//         cmd->status_exit = msh->exit_status;
//         cmd = cmd->next;
//     }
// }


int count_commands(t_command *cmd)
{
    int count;
    
    count = 0;
    while(cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return (count);
}

int create_pipe_if_needed(int i, int total, int pipefd[2], t_msh *msh)
{
    if (i < total - 1)
    {
        if(pipe(pipefd) == -1)
        {
            perror("minishell: pipe");
            free_command_list(msh->cmds);
            free_env_list(&msh->dict_env);
            free(msh->input);
            exit (1);
        }
    }
    else
    {
        pipefd[0] = -1;
        pipefd[1] = -1;
    }
    return (0);
}

void child_process(t_command *cmd, t_msh *msh, t_exec_ctx *ctx)
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
    exec_external(cmd, msh);
    exit(1);
}

void parent_pipe_cleanup(t_exec_ctx *ctx)
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

void wait_all(int *exit_status)
{
    int status;

    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            *exit_status = WEXITSTATUS(status);
    }
}

static void init_exec_ctx(t_exec_ctx *ctx, int total)
{
    ctx->index = 0;
    ctx->total = total;
    ctx->prev_pipe[0] = -1;
    ctx->prev_pipe[1] = -1;
    ctx->next_pipe[0] = -1;
    ctx->next_pipe[1] = -1;
}

void execute(t_msh *msh)
{
    t_command *cmd;
    t_exec_ctx ctx;
    pid_t pid;

    cmd = msh->cmds;
    init_exec_ctx(&ctx, count_commands(cmd));
    if (ctx.total == 1 && is_builtin(cmd->argv[0]))
    {
        int stdin_backup = dup(STDIN_FILENO);
	    int stdout_backup = dup(STDOUT_FILENO);

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
