/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:01:17 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/08 18:48:10 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

void	set_env_value(t_env **head, const char *key, const char *value)
{
	t_env	*current;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	add_env_node(head, key, value);
}

void	remove_env_key(t_env **head, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

bool	env_exists(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

int	exec_program_name(t_command *cmd, t_msh *msh)
{
	char	**envp;

	if (ft_strcmp(cmd->argv[0], "./minishell") != 0)
		return (1);
	envp = env_to_array(msh->dict_env);
	if (!envp)
		return (1);
	execve("./minishell", cmd->argv, envp);
	perror("execve failed");
	exit(1);
}
