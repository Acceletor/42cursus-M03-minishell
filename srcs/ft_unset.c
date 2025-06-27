/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:49:42 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/26 20:24:03 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_unset(t_command *cmd, t_env **env_list)
{
    int i;

    i = 1;
    while (cmd->argv[i])
    {
        if (!is_valid_identifier(cmd->argv[i]))
        {
            ft_putstr_fd("minishell unset", 2);
            ft_putstr_fd(cmd->argv[i], 2);
            ft_putstr_fd(cmd->argv[i], 2);
        }
        else
        {
            remove_env_key(env_list, cmd->argv[i]);
        }
        i++;
    }
    return 0;
}
