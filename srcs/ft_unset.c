/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:49:42 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/20 21:20:04 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int is_valid_identifier(const char *key)
{
    int i;

    if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
        return (0);
    i = 1;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int ft_unset(t_builtin *cmd, t_env **env_list)
{
    int i;

    i = 1;
    while (cmd->args[i])
    {
        if (!is_valid_identifier(cmd->args[i]))
        {
            ft_putstr_fd("minishell unset", 2);
            ft_putstr_fd(cmd->args[i], 2);
            ft_putstr_fd(cmd->args[i], 2);
        }
        else
        {
            remove_env_key(env_list, cmd->args[i]);
        }
        i++;
    }
    return 0;
}
