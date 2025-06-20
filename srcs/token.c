/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:04:52 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/20 22:48:12 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

t_token	*token_stream(char *input, t_env *env)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			i++;
			continue ;
		}
		if (handle_special_tokens(input, &i, &tokens))
			continue ;
		if (handle_quotes(input, &i, &tokens, env))
			continue ;
		handle_word(input, &i, &tokens);
	}
	return (tokens);
}
