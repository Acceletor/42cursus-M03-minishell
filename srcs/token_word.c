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

char *extract_double_quote(char *input, int *i, t_msh *msh)
{
    char *result;
    char *part;
    
    (*i)++;
    result = ft_strdup("");
    while (input[*i] && input[*i] != '"')
    {
        if (input[*i] == '$')
            part = extract_dollar_value(msh->input, i, msh);
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

void	handle_word(t_msh *msh, int *i, t_token **tokens)
{
	char	*word;
	char	*part;

	word = ft_strdup("");
	while (msh->input[*i] && msh->input[*i] != ' ' && msh->input[*i] != '|'
		&& msh->input[*i] != '<' && msh->input[*i] != '>')
	{
		if (msh->input[*i] == '\'')
			part = extract_single_quote(msh->input, i);
        else if (msh->input[*i] == '"')
            part = extract_double_quote(msh->input, i, msh);
        else if (msh->input[*i] == '$')
            part = extract_dollar_value(msh->input, i, msh);
        else
            part = extract_plain_text(msh->input, i);
        word = strjoin_and_free(word, part);
        if (!word)
            return ;
	}
	add_token(tokens, new_token(word, TOKEN_WORD));
	free(word);
}
