/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:04:52 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/16 22:10:04 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_quotes(char *input, int *i, t_token **tokens)
{
	char	quote;
	int		start;
	char	*quoted;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		quote = input[(*i)++];
		start = *i;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		quoted = ft_strndup(&input[start], *i - start);
		add_token(tokens, new_token(quoted, TOKEN_WORD));
		free(quoted);
		if (input[*i] == quote)
			(*i)++;
		return (1);
	}
	return (0);
}

void	handle_word(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*word;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
		(*i)++;
	word = ft_strndup(&input[start], *i - start);
	add_token(tokens, new_token(word, TOKEN_WORD));
	free(word);
}


t_token	*token_stream(char *input)
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
		if (handle_quotes(input, &i, &tokens))
			continue ;
		handle_word(input, &i, &tokens);
	}
	return (tokens);
}
