/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:58:48 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/16 17:46:57 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_export(t_builtin *cmd, t_env **env_list)
{
    int i;
    char *key;
    char *value;
    char *equal_sign;
    int key_len;

    while(cmd->args[i])
    {
        equal_sign = ft_strchr(cmd->args[i], '=');
        if(equal_sign)
        {
            key_len = equal_sign - cmd->args[i];
            key = ft_strndup(cmd->args[i], key_len);
            value = ft_strdup(equal_sign + 1);
            set_env_value(env_list, key, value);
            free(key);
            free(value);
        }
        i++;
    }
    return 0;
}

//create a checker for invalid keys