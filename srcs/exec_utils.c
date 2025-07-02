/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:28:42 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/02 23:24:52 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *strjoin_three_and_free(char *s1, char *s2, char *s3)
{
    char *temp;
    char *res;

    temp = ft_strjoin(s1, s2);
    if (!temp)
        return NULL;
    res = ft_strjoin(temp, s3);
    free(temp);
    return res;
}

void    free_array(char **arr)
{
    int i;
    
    if(!arr)
        return ;
    i = 0;
    while(arr[i])
        free(arr[i++]);
    free(arr);
}

char *get_path_name(t_command *cmd, t_env *env)
{
    char *path;
    char **dirs;
    char *temp;
    char *res;
    int i = 0;

    path = get_env_value(env, "PATH");
    dirs = ft_split(path, ':');
    while (dirs[i])
    {
        temp = strjoin_three_and_free(dirs[i], "/", cmd->argv[0]);
        if (!temp)
        {
            i++;
            continue;
        }
        if (access(temp, X_OK) == 0)
        {
            res = ft_strdup(temp);
            free(temp);
            free_array(dirs);
            return res;
        }
        free(temp);
        i++;
    }
    free_array(dirs);
    return NULL;
}

