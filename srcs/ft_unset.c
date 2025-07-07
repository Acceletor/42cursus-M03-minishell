/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:49:42 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/07 18:46:21 by eeravci          ###   ########.fr       */
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

int	ft_unset(t_command *cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!is_valid_identifier(cmd->argv[i]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			remove_env_key(env_list, cmd->argv[i]);
		}
		i++;
	}
	return (0);
}
