/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:28:42 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/07 19:05:06 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*strjoin_three_and_free(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, s3);
	free(temp);
	return (res);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*join_key_value(char *key, char *value)
{
	int		len_key;
	int		len_value;
	char	*res;

	len_key = ft_strlen(key);
	len_value = ft_strlen(value);
	res = malloc(sizeof(char) * (len_key + 1 + len_value + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, key, len_key + 1);
	res[len_key] = '=';
	ft_strlcpy(res + len_key + 1, value, len_value + 1);
	return (res);
}

char	*get_path_name(t_command *cmd, t_env *env)
{
	char	**dirs;
	char	*temp;
	char	*result;
	int		i;

	i = 0;
	dirs = ft_split(get_env_value(env, "PATH"), ':');
	if (!dirs)
		return (NULL);
	while (dirs[i])
	{
		temp = strjoin_three_and_free(dirs[i], "/", cmd->argv[0]);
		if (temp && access(temp, X_OK) == 0)
		{
			result = ft_strdup(temp);
			free(temp);
			free_array(dirs);
			return (result);
		}
		free(temp);
		i++;
	}
	free_array(dirs);
	return (NULL);
}

char	**env_to_array(t_env *env_list)
{
	char	**env;
	t_env	*temp;
	int		len;
	int		i;

	len = 0;
	temp = env_list;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (NULL);
	temp = env_list;
	i = 0;
	while (temp)
	{
		env[i] = join_key_value(temp->key, temp->value);
		i++;
		temp = temp->next;
	}
	env[i] = NULL;
	return (env);
}
