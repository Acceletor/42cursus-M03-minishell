/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:46:09 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/07 18:46:10 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_env_entry(t_env *env)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	if (env->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static void	sort_env_array(t_env **array, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export_list(t_env *env_list)
{
	int		i;
	int		size;
	t_env	**array;
	t_env	*env;

	size = env_list_size(env_list);
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return ;
	env = env_list;
	i = 0;
	while (env)
	{
		array[i++] = env;
		env = env->next;
	}
	sort_env_array(array, size);
	i = 0;
	while (i < size)
		print_env_entry(array[i++]);
	free(array);
}
