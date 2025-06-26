/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:49:27 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/20 21:13:09 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// implements the echo builtin command,
// printing arguments with optional newline suppression.
// supports multiple -n options and prints a space between each argument.
// we can also create helperfunct to check n_option to reduce code lines
int ft_echo(t_command *cmd)
{
    int i;
    int n_option;

    i = 1;
    n_option = 0;
    while (cmd->argv[i] && ft_strcmp(cmd->argv[i], "-n") == 0)
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
    if (! n_option)
        write(1, "\n", 1);
    return (0);
}
