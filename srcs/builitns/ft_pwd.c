/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:49:33 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/15 13:08:02 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(char **argv)
{
	char	*pwd;

	(void)argv;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("cwd error\n", 2);
		return (2);
	}
	else
		ft_putstr_fd(pwd, 2);
	ft_putchar_fd('\n', 1);
	return (1);
}
