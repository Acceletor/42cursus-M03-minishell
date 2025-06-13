/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:36:33 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/13 22:47:24 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	add_env_node(t_env **head, const char *key, const char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	size_t	key_len;
	char	*p_equal;
	char	*key;
	char	*value;

	head = NULL;
	while (*envp)
	{
		p_equal = ft_strchr(*envp, '=');
		if (p_equal)
		{
			key_len = p_equal - *envp;
			key = ft_strndup(*envp, key_len);
			value = ft_strdup(p_equal + 1);
			add_env_node(&head, key, value);
			free(key);
			free(value);
		}
		envp++;
	}
	return (head);
}

void	free_env_list(t_env **head)
{
	t_env	*current;
	t_env	*temp;

	current = *head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	*head = NULL;
}

void	print_env_list(t_env *head)
{
	while (head)
	{
		ft_printf("%s => %s\n", head->key, head->value);
		head = head->next;
	}
}
