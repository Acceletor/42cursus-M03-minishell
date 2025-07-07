/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:58:48 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/07 18:45:59 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_identifier(const char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_error(const char *arg)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	handle_invalid_export(const char *arg, char *key, char *value)
{
	print_export_error(arg);
	free(key);
	free(value);
	return (1);
}

static int	process_export_arg(const char *arg, t_env **env_list)
{
	char	*key;
	char	*value;
	char	*equal_pos;
	bool	exists;

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
		return (handle_invalid_export(arg, key, value));
	exists = env_exists(*env_list, key);
	if (!exists || (value != NULL && exists))
		set_env_value(env_list, key, value);
	free(key);
	free(value);
	return (0);
}

int	ft_export(t_command *cmd, t_env **env_list)
{
	int	i;
	int	status;

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
