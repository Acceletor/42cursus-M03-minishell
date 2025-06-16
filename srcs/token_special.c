#include "../include/minishell.h"

int handle_pipe(char *input, int *i, t_token **tokens)
{
    if (input[*i] == '|')
    {
        add_token(tokens, new_token("|", TOKEN_PIPE));
        (*i)++;
        return (1);
    }
    return (0);
}

int	handle_redir_out(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, new_token(">>", TOKEN_APPEND));
		*i += 2;
		return (1);
	}
	if (input[*i] == '>')
	{
		add_token(tokens, new_token(">", TOKEN_REDIR_OUT));
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_redir_in(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(tokens, new_token("<<", TOKEN_HEREDOC));
		*i += 2;
		return (1);
	}
	if (input[*i] == '<')
	{
		add_token(tokens, new_token("<", TOKEN_REDIR_IN));
		(*i)++;
		return (1);
	}
	return (0);
}

int handle_special_tokens(char *input, int *i, t_token **tokens)
{
    if (handle_pipe(input, i, tokens))
		return (1);
    if (handle_redir_out(input, i, tokens))
        return (1);
    if (handle_redir_in(input, i, tokens))
        return (1);
    return (0);
}
