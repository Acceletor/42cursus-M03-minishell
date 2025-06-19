/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:54:33 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/19 23:18:11 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

/*if (is_builtin(cmd->args[0]) && !in_pipeline)
{
    // Run in parent without fork
    execute_builtins(cmd, shell);
}
else
{
    // Run in child with fork
    pid_t pid = fork();
    if (pid == 0)
    {
        // Child
        if (is_builtin(cmd->args[0]))
            exit(execute_builtins(cmd, shell));
        else
            execve(...);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}
 */

