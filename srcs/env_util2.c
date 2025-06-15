/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:01:17 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/15 13:12:08 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_env_value(t_env *env_list, const char *key)
{
    while(env_list)
    {
        if(ft_strcmp(env_list->key, key) == 0)
            return (env_list->value);
        env_list = env_list->next;
    }
    return NULL;
}

void set_env_value(t_env **head, const char *key, const char *value)
{
    t_env *current;

    current = *head;
    while(current)
    {
        if(ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return ;
        }
        current = current->next;
    }
    add_env_node(head, key, value);
}

void remove_env_key(t_env **head, const char *key)
{
    t_env *current;
    t_env *prev;

    current = *head;
    prev = NULL;
    while(current)
    {
        if(ft_strcmp(current->key, key) == 0)
        {
            if(prev)
                prev->next = current->next;
            else
                *head = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return ;
        }
        prev = current;
        current = current->next;
    }
}
