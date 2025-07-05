/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:54:33 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/05 21:19:04 by eeravci          ###   ########.fr       */
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
  //  else if (ft_strcmp(cmd->argv[0], "exit") == 0)
    //    return (ft_exit(cmd));

    return (1);
}
//complete it and think all cases
static void	execve_child(char *path, t_command *cmd, char **envp)
{
	execve(path, cmd->argv, envp);
	perror(cmd->argv[0]);
	exit(1);
}

static int	handle_fork(char *path, t_command *cmd, char **envp)
{
	pid_t	pid;
	int		status = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		execve_child(path, cmd, envp);
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_external(t_command *cmd, t_msh *shell)
{
	char	*path;
	char	**envp;
	int		result;

	path = get_path_name(cmd, shell->dict_env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		return (127);
	}
	envp = env_to_array(shell->dict_env);
	if (!envp)
		return (free(path), 1);
	result = handle_fork(path, cmd, envp);
	free(path);
	free_array(envp);
	return (result);
}

void execute(t_msh *msh)
{
    t_command *cmd;
    
    cmd = msh->cmds;
    while(cmd)
    {
        if (is_builtin(cmd->argv[0]))
            msh->exit_status = execute_builtins(cmd, msh);
        else
            //print_command_list(cmd);
            msh->exit_status = exec_external(cmd, msh);
        cmd->status_exit = msh->exit_status;
        cmd = cmd->next;
    }
}

