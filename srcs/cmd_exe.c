/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:54:33 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/20 21:29:31 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtin(char *cmd)
{
    return (
        ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0
    );
}

int execute_builtins(t_builtin *cmd, t_msh *shell)
{
    if (ft_strcmp(cmd->args[0], "echo") == 0)
        return ft_echo(cmd);
    else if (ft_strcmp(cmd->args[0], "cd") == 0)
        return ft_cd(cmd, shell);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        return ft_pwd(cmd);  // ✅ make sure ft_pwd takes t_builtin *cmd
    else if (ft_strcmp(cmd->args[0], "export") == 0)
        return ft_export(cmd, &shell->dict_env);  // ✅ fix pointer type
    else if (ft_strcmp(cmd->args[0], "unset") == 0)
        return ft_unset(cmd, &shell->dict_env);  // ✅ already correct
    else if (ft_strcmp(cmd->args[0], "env") == 0)
        return ft_env(cmd, shell->dict_env);  // ✅ correct type
    else if (ft_strcmp(cmd->args[0], "exit") == 0)
        return ft_exit(cmd, shell->last_exit_code);
    
    return -1;
}
