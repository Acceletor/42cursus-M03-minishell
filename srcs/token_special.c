/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:04:59 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/07/09 23:00:57 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_special_token(const char *str)
{
	return (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str,
			"<") || !ft_strcmp(str, "<<") || !ft_strcmp(str, "|"));
}

char	*extract_special_chunk(const char *input, int *i)
{
	int		start;
	char	*chunk;

	start = *i;
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	chunk = ft_strndup(&input[start], *i - start);
	return (chunk);
}

void	add_token_by_type(char *chunk, t_token **tokens)
{
	if (!ft_strcmp(chunk, ">"))
		add_token(tokens, new_token(">", TOKEN_REDIR_OUT));
	else if (!ft_strcmp(chunk, ">>"))
		add_token(tokens, new_token(">>", TOKEN_APPEND));
	else if (!ft_strcmp(chunk, "<"))
		add_token(tokens, new_token("<", TOKEN_REDIR_IN));
	else if (!ft_strcmp(chunk, "<<"))
		add_token(tokens, new_token("<<", TOKEN_HEREDOC));
	else if (!ft_strcmp(chunk, "|"))
		add_token(tokens, new_token("|", TOKEN_PIPE));
}

int	handle_special_tokens(char *input, int *i, t_token **tokens)
{
	char	*chunk;

	if (!ft_strchr("><|", input[*i]))
		return (0);
	chunk = extract_special_chunk(input, i);
	if (!chunk)
		return (-1);
	if (!is_valid_special_token(chunk))
	{
		ft_putstr_fd("minishell: syntax error: unexpected token: ", 2);
		ft_putstr_fd(chunk, 2);
		ft_putchar_fd('\n', 2);
		free(chunk);
		return (-1);
	}
	add_token_by_type(chunk, tokens);
	free(chunk);
	return (1);
}
