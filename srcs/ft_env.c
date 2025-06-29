/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:49:30 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/26 20:16:51 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_command *cmd, t_env *env_list)
{
	if (cmd->argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	// while (env_list)
	// {
	// 	if (env_list->value)
	// 	{
	// 		ft_putstr_fd(env_list->key, 1);
	// 		ft_putstr_fd("=", 1);
	// 		ft_putstr_fd(env_list->value, 1);
	// 		ft_putchar_fd('\n', 1);
	// 	}
	// 	env_list = env_list->next;
	// }
	print_env_list(env_list);
	return (0);
}
