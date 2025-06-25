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

static int	is_valid_char(char c)
{
	return (
		ft_isalnum(c) ||
		ft_strchr(" |><'\"$", c)
	);
}

t_token	*token_stream(t_msh *msh)
{
	t_token	*tokens;
	int		i;
	int		ret;

	i = 0;
	tokens = NULL;
	while (msh->input[i])
	{
		if (msh->input[i] == ' ')
		{
			i++;
			continue ;
		}
		ret = handle_special_tokens(msh->input, &i, &tokens);
		if (ret == 1)
			continue ;
		if (ret == -1)
		{
			free_tokens(&tokens);
			return (NULL);
		}
		if (!is_valid_char(msh->input[i]))
		{
			ft_putstr_fd("minishell: syntax error near unexpected character: ", 2);
			write(2, &msh->input[i], 1);
			write(2, "\n", 1);
			free_tokens(&tokens);
			return (NULL);
		}
		if (!handle_word(msh, &i, &tokens))
		{
			free_tokens(&tokens);
			return (NULL);
		}
		else
			i++;
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

int	handle_word(t_msh *msh, int *i, t_token **tokens)
{
	char	*word;
	char	*part;

	word = ft_strdup("");
    if (!word)
        return (0);
	while (msh->input[*i] && !ft_strchr(" |<>", msh->input[*i]))
	{
        part = extract_word_part(msh, i);
        if (!part)
        {
            free(word);
            msh->exit_status = 2;
            return (0);
        }
        word = strjoin_and_free(word, part);
        if (!word)
            return (0);  
	}
	add_token(tokens, new_token(word, TOKEN_WORD));
	free(word);
	return (1);
}
