/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:49:30 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/19 22:04:05 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_builtin *cmd, t_env *env_list)
{
	if (cmd->args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	while (env_list)
	{
		if (env_list->value)
		{
			ft_putstr_fd(env_list->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env_list->value, 1);
			ft_putchar_fd('\n', 1);
		}
		env_list = env_list->next;
	}
	return (0);
}
