/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:41 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/12 22:23:29 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_msh *msh)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (msh->cmds->argc == 0)
		free_msh(msh, 0);
	if (!(is_numeric(msh->cmds->argv[1])))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(msh->cmds->argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free_msh(msh, 2);
	}
	else if (msh->cmds->argc > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(msh->cmds->argv[1]);
	free_msh(msh, (unsigned char)exit_code);
	return (0);
}
