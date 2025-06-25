/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:35:49 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/25 23:58:14 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *extract_single_quote(char *input, int *i)
{
    int start;
    char *text;

    (*i)++;
    start = *i;
    while (input[*i] && input[*i] != '\'')
        (*i)++;
    if (input[*i] != '\'')
    {
        ft_putstr_fd("minishell: syntax error: unclosed single quote\n", 2);
        return (NULL);
    }
    text = ft_strndup(&input[start], *i - start);
    (*i)++;
    return (text);
}

static char	*extract_double_quoted_text(char *input, int *i)
{
	int		start;

	start = *i;
	while (input[*i] && input[*i] != '"' && input[*i] != '$')
		(*i)++;
	return (ft_strndup(&input[start], *i - start));
}

static char	*handle_quoted_part(char *input, int *i, t_msh *msh)
{
	if (input[*i] == '$')
		return (extract_dollar_value(msh->input, i, msh));
	else
		return (extract_double_quoted_text(input, i));
}

char *extract_double_quote(char *input, int *i, t_msh *msh)
{
	char *result;
    char *part;
    
    (*i)++;
    result = ft_strdup("");
    while (input[*i] && input[*i] != '"')
    {
        part = handle_quoted_part(input, i, msh);
        if (!part)
        {
            free(result);
            return (NULL);
        }
        result = strjoin_and_free(result, part);
        if (!result)
            return (NULL);
    }
    if (input[*i] != '"')
    {
        ft_putstr_fd("minishell: syntax error: unclosed double quote\n", 2);
        free(result);
        return (NULL);
    }
    (*i)++;
    return (result);
}

char *extract_plain_text(char *input, int *i)
{
	int	start = *i;
	while (input[*i] && !ft_strchr(" |<>\"'$", input[*i]))
		(*i)++;
	return ft_strndup(&input[start], *i - start);
}
