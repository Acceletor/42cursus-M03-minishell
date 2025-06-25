/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:54:33 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/25 19:15:23 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
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

int execute_builtins(t_command *cmd, t_msh *shell)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (1);
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return (ft_echo(cmd));
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return ft_cd(cmd, shell);
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        return ft_pwd(cmd);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        return ft_export(cmd, &shell->dict_env);
    // else if (ft_strcmp(cmd->args[0], "unset") == 0)
    //     return ft_unset(cmd, &shell->dict_env);
    // else if (ft_strcmp(cmd->args[0], "env") == 0)
    //     return ft_env(cmd, shell->dict_env);
    // else if (ft_strcmp(cmd->args[0], "exit") == 0)
    //     return ft_exit(cmd, shell->last_exit_code);
    return (1);
}

void execute(t_msh *msh)
{
    t_command *cmd;
    
    cmd = msh->cmds;
    while(cmd)
    {
        if (is_builtin(cmd->argv[0]))
            msh->exit_status = execute_builtins(cmd, msh);
        else
            print_command_list(cmd);
            // msh->exit_status = exec_external(cmd, msh);
        cmd->status_exit = msh->exit_status;
        cmd = cmd->next;
    }
}