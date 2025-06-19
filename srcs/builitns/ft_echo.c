/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:49:27 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/19 22:49:59 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// implements the echo builtin command,
// printing arguments with optional newline suppression.
// supports multiple -n options and prints a space between each argument.
// we can also create helperfunct to check n_option to reduce code lines
int ft_echo(t_builtin *cmd)
{
    int i;
    int n_option;

    i = 1;
    n_option = 0;
    if (cmd->argc > 1)
    {
        while (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
        {
            n_option = 1;
            i++;
        }
        while (cmd->args[i])
        {
            ft_putstr_fd(cmd->args[i], 1);
            if (cmd->args[i + 1] && cmd->args[i][0] != '\0')
                write(1, " ", 1);
            i++;
        }
    }
    if (n_option == 0)
        write(1, "\n", 1);
    cmd->status_exit = 0;
    return (cmd->status_exit);
}
