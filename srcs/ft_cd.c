/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:48:51 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/20 21:12:57 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// updates the PWD and OLDPWD environment variables after a successful directory change
static void update_pwd(t_msh *shell)
{
    char *cwd;
    char *old_pwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
        return;
    old_pwd = get_env_value(shell->dict_env, "PWD");
    if (old_pwd)
        set_env_value(&shell->dict_env, "OLDPWD", old_pwd);
    else
        set_env_value(&shell->dict_env, "OLDPWD", "");
    set_env_value(&shell->dict_env, "PWD", cwd);
    free(cwd);
}

// If no argument is passed to 'cd',
// this navigates to the HOME directory if it's set.
static int check_cd(t_command *cmd, t_msh *shell)
{
    char *home_path;

    if (cmd->argv[1] == NULL)
    {
        home_path = get_env_value(shell->dict_env, "HOME");
        if (!home_path)
        {
            ft_putstr_fd("cd: home not set\n", 2);
            return 1;
        }
        if (chdir(home_path) != 0)
        {
            perror("cd");
            return 1;
        }
        update_pwd(shell);
        return 0;
    }
    return -1;
}

// Handles cd - by switching
// to the OLDPWD directory and printing it.
static int get_old_pwd(t_command *cmd, t_msh *shell)
{
    char *old_pwd;

    if (ft_strcmp(cmd->argv[1], "-") == 0)
    {
        old_pwd = get_env_value(shell->dict_env, "OLDPWD");
        if (!old_pwd)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
            return 1;
        }
        if (chdir(old_pwd) != 0)
        {
            perror("cd");
            return 1;
        }
        ft_putstr_fd(old_pwd, 1);
        ft_putstr_fd("\n", 1);
        update_pwd(shell);
        return 0;
    }
    return -1;
}

// handles the cd command logic including argument validation,
//  special cases, and directory switching
int ft_cd(t_command *cmd, t_msh *shell)
{
    int res;

    if (cmd->argv[2] != NULL)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return 1;
    }
    res = check_cd(cmd, shell);
    if (res != -1)
        return res;
    res = get_old_pwd(cmd, shell);
    if (res != -1)
        return res;
    if (chdir(cmd->argv[1]) != 0)
    {
        perror("cd");
        return 1;
    }
    update_pwd(shell);
    return 0;
}
