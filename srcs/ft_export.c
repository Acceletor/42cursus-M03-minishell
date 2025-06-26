/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:58:48 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/26 19:14:22 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void print_export_list(t_env *env_list)
{
	int	i;
	int size;
	t_env **array;
	t_env *env;

	size = env_list_size(env_list);
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return ;
	env = env_list;
	i = 0;
	while (env)
	{
		array[i++] = env;
		env = env->next;
	}
	sort_env_array(array, size);
	i = 0;
	while (i < size)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(array[i]->key, 1);
		if (array[i]->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(array[i]->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
	free(array);
}

static int	process_export_arg(const char *arg, t_env **env_list)
{
	char	*key;
	char	*value;
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		key = ft_strndup(arg, equal_pos - arg);
		value = ft_strdup(equal_pos + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (!key || !is_valid_identifier(key))
	{
		print_export_error(arg);
		free(key);
		free(value);
		return (1);
	}
	set_env_value(env_list, key, value);
	free(key);
	free(value);
	return (0);
}

int	ft_export(t_command *cmd, t_env **env_list)
{
	int	i;
	int status;

	status = 0;
	if (!cmd->argv[1])
	{
		print_export_list(*env_list);
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (process_export_arg(cmd->argv[i], env_list) != 0)
			status = 1;
		i++;
	}
	return (status);
}
