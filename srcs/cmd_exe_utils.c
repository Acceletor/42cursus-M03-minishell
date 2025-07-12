/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:00:36 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/12 19:14:30 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtins(t_command *cmd, t_msh *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(cmd));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd, &shell->dict_env));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd, &shell->dict_env));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(cmd, shell->dict_env));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exit(cmd));
	return (1);
}

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	create_pipe_if_needed(int i, int total, int pipefd[2], t_msh *msh)
{
	if (i < total - 1)
	{
		if (pipe(pipefd) == -1)
		{
			perror("minishell: pipe");
			free_command_list(msh->cmds);
			free_env_list(&msh->dict_env);
			free(msh->input);
			exit(1);
		}
	}
	else
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
	}
	return (0);
}

char	*resolve_cmd_path(t_command *cmd, t_msh *shell)
{
	char	*path;

	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (access(cmd->argv[0], F_OK) != 0)
		{
			ft_printf("minishell: %s: No such file or directory\n",
				cmd->argv[0]);
			free_msh(shell, 127);
		}
		if (access(cmd->argv[0], X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->argv[0]);
			free_msh(shell, 126);
		}
		return (ft_strdup(cmd->argv[0]));
	}
	path = get_path_name(cmd, shell->dict_env);
	if (!path)
	{
		ft_printf("minishell: command not found: %s\n", cmd->argv[0]);
		free_msh(shell, 127);
	}
	return (path);
}
