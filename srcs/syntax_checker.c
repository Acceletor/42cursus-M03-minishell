#include "../include/minishell.h"

int check_pipe_syntax(t_token *tokens)
{
    if (!tokens)
        return (0);
    if (tokens->type == TOKEN_PIPE)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `|'", STDERR_FILENO);
        return (1);
    }
    while (tokens)
    {
        if (tokens->type == TOKEN_PIPE)
        {
            tokens = tokens->next;
            if (!tokens || tokens->type == TOKEN_PIPE)
            {
                ft_putendl_fd("minishell: syntax error near unexpected token `|'", STDERR_FILENO);
                return (1);
            }
        }
        else
            tokens = tokens->next;
    }
    return (0);

}