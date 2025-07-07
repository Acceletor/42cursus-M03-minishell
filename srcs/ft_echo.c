/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:49:27 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/07 18:45:42 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// check -n cases
static int	is_valid_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_command *cmd)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	while (cmd->argv[i] && is_valid_n_option(cmd->argv[i]))
	{
		n_option = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}
