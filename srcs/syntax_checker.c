/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:23:33 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/07/10 22:12:17 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_pipe_syntax(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token '|'",
			STDERR_FILENO);
		return (1);
	}
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			tokens = tokens->next;
			if (!tokens || tokens->type == TOKEN_PIPE)
			{
				ft_printf("minishell:");
				ft_putendl_fd(" syntax error near unexpected token '|'",
					STDERR_FILENO);
				return (1);
			}
		}
		else
			tokens = tokens->next;
	}
	return (0);
}

int	check_redirect_syntax(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type >= TOKEN_REDIR_OUT && tokens->type <= TOKEN_HEREDOC)
		{
			if (!tokens->next || tokens->next->type != TOKEN_WORD)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token ",
					STDERR_FILENO);
				if (tokens->next)
					ft_putstr_fd(tokens->next->value, STDERR_FILENO);
				else
					ft_putstr_fd("`newline'", STDERR_FILENO);
				ft_putchar_fd('\n', STDERR_FILENO);
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
