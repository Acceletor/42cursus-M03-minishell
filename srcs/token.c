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

t_token	*token_stream(t_msh *msh)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (msh->input[i])
	{
		if (msh->input[i] == ' ')
		{
			i++;
			continue ;
		}
		if (handle_special_tokens(msh->input, &i, &tokens))
			continue ;
		handle_word(msh, &i, &tokens);
	}
	return (tokens);
}

static char	*extract_word_part(t_msh *msh, int *i)
{
	if (msh->input[*i] == '\'')
		return (extract_single_quote(msh->input, i));
	else if (msh->input[*i] == '"')
		return (extract_double_quote(msh->input, i, msh));
	else if (msh->input[*i] == '$')
		return (extract_dollar_value(msh->input, i, msh));
	else
		return (extract_plain_text(msh->input, i));
}

void	handle_word(t_msh *msh, int *i, t_token **tokens)
{
	char	*word;
	char	*part;

	word = ft_strdup("");
    if (!word)
        return ;
	while (msh->input[*i] && !ft_strchr(" |<>", msh->input[*i]))
	{
        part = extract_word_part(msh, i);
        if (!part)
        {
            free(word);
            msh->exit_status = 2;
            return ;
        }
        word = strjoin_and_free(word, part);
        if (!word)
            return ;  
	}
	add_token(tokens, new_token(word, TOKEN_WORD));
	free(word);
}
