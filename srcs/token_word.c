#include "../include/minishell.h"

char *extract_single_quote(char *input, int *i)
{
    int start;
    char *text;

    (*i)++;
    start = *i;
    while (input[*i] && input[*i] != '\'')
        (*i)++;
    text = ft_strndup(&input[start], *i - start);
    if (input[*i] == '\'')
        (*i)++;
    return (text);
}

char *extract_double_quote(char *input, int *i, t_env *env)
{
    char *result;
    char *part;
    
    (*i)++;
    result = ft_strdup("");
    while (input[*i] && input[*i] != '"')
    {
        if (input[*i] == '$')
        {
            if (ft_isalpha(input[*i + 1]) || input[*i + 1] == '_' || 
                input[*i + 1] == '{' || input[*i + 1] == '?')
                part = extract_dollar_value(input, i, env);
            else
            {
                part = ft_strndup(&input[*i], 1);
                (*i)++;
            }
        }
        else
            part = extract_plain_text(input, i);
        result = strjoin_and_free(result, part);
        if (!result)
            return (NULL);
    }
    if (input[*i] == '"')
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

void	handle_word(char *input, int *i, t_token **tokens, t_env *env)
{
	char	*word;
	char	*part;

	word = ft_strdup("");
	while (input[*i] && input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'')
			part = extract_single_quote(input, i);
        else if (input[*i] == '"')
            part = extract_double_quote(input, i, env);
        else if (input[*i] == '$')
        {
            if (ft_isalpha(input[*i + 1]) || input[*i + 1] == '_' ||
                input[*i + 1] == '{' || input[*i + 1] == '?')
                part = extract_dollar_value(input, i, env);
            else
            {
                part = ft_strndup(&input[*i], 1);
                (*i)++;
            }
        } 
        else
            part = extract_plain_text(input, i);
        word = strjoin_and_free(word, part);
        if (!word)
            return ;
	}
	add_token(tokens, new_token(word, TOKEN_WORD));
	free(word);
}
