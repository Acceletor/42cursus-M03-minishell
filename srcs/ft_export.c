/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:58:48 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/20 21:13:23 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	process_export_arg(const char *arg, t_env **env_list);
static int	is_valid_identifier(const char *key);
static void	print_export_error(const char *arg);

int	ft_export(t_builtin *cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		process_export_arg(cmd->args[i], env_list);
		i++;
	}
	return (0);
}

static int	process_export_arg(const char *arg, t_env **env_list)
{
	char	*key;
	char	*value;
	char	*equal_sign;
	int		key_len;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	key_len = equal_sign - arg;
	key = ft_strndup(arg, key_len);
	value = ft_strdup(equal_sign + 1);
	if (!key || !value)
		return (1);
	if (!is_valid_identifier(key))
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
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
