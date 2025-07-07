/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:49:33 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/07 18:46:15 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_command *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: pwd: getcwd failed\n", 2);
		return (1);
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);
}
