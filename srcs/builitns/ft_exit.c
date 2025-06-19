/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:41 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/19 22:54:25 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int is_numeric(const char *str)
{
    int i;

    i = 0;
    if (!str || !*str)
        return 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int ft_exit(t_builtin *cmd, int last_exit_code)
{
    long exit_code;

    ft_putstr_fd("exit\n", STDERR_FILENO);
    if (cmd->argc == 1)
        exit(last_exit_code);
    if (!is_numeric(cmd->args[1]))
    {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(cmd->args[1], STDERR_FILENO);
        ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
        exit(2);
    }
    if (cmd->argc > 2)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return (1);
    }
    exit_code = ft_atoi(cmd->args[1]);
    exit((unsigned char)exit_code);
}
