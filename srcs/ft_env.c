/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:49:30 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/07 00:10:36 by eeravci          ###   ########.fr       */
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
	print_env_list(env_list);
	return (0);
}
