/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:33:42 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/20 21:34:07 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_builtin *parse_input_to_builtin(char *input)
{
    t_builtin *cmd = malloc(sizeof(t_builtin));
    if (!cmd)
        return NULL;

    cmd->args = ft_split(input, ' '); // basic split by space
    if (!cmd->args)
        return NULL;

    // Count arguments
    int count = 0;
    while (cmd->args[count])
        count++;
    cmd->argc = count;

    return cmd;
}

void free_cmd(t_builtin *cmd)
{
    int i = 0;
    while (cmd->args && cmd->args[i])
    {
        free(cmd->args[i]);
        i++;
    }
    free(cmd->args);
    free(cmd);
}

int main(int argc, char **argv, char **envp)
{
    t_msh shell;
    char *input;
    t_builtin *cmd;

    (void)argc;
    (void)argv;

    // Init shell and env
    shell.dict_env = init_env(envp);
    shell.last_exit_code = 0;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;
        if (*input)
            add_history(input);

        cmd = parse_input_to_builtin(input);
        free(input);

        if (!cmd || !cmd->args || !cmd->args[0])
        {
            free_cmd(cmd);
            continue;
        }

        if (ft_strcmp(cmd->args[0], "exit") == 0)
        {
            ft_exit(cmd, shell.last_exit_code);
        }

        if (execute_builtins(cmd, &shell) == -1)
        {
            ft_putstr_fd("minishell: command not found: ", 2);
            ft_putstr_fd(cmd->args[0], 2);
            ft_putchar_fd('\n', 2);
        }

        free_cmd(cmd);
    }

    free_env_list(&shell.dict_env);
    return (0);
}
