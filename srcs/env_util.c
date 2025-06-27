/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:36:33 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/20 22:31:11 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
    Creates a new environment variable node with given the key and value.
    Returns a pointer to the newly created node, or NULL if memory allocation
	 fails
*/
t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

/*
Adds a new environment variable node to the end od the linked list
If the list is empty, the new node becomes the head
*/
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

/*
Initializes the linked list of env variables usinf the provide 'envp' array.
Each strinf in 'envp' is split into key and value by the '='
Returns a pointer to the head of the list.
*/
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

/*
Frees all memory used by the environment variable linked list
Sets the head pointer to NULL after freeing
*/
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

/*
Prints all environmet variables in linked list
    key => value
*/
void	print_env_list(t_env *head)
{
	while (head)
	{
		ft_printf("%s => %s\n", head->key, head->value);
		head = head->next;
	}
}
