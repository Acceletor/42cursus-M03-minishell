/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:23:37 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/19 23:47:45 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Extracts a variable name like USER from a string like $USER.
*/
char	*extract_var_name(const char *str, int *i)
{
	int	start;
	int	len;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	return (ft_strndup(&str[start], len));
}

/*
Handles $VARIABLE expansion and appends the expanded value to the result string.
*/
char	*append_var_val(char *result, const char *str, int *i, t_env *env)
{
	char	*var;
	char	*val;
	char	*temp;

	(*i)++;
	var = extract_var_name(str, i);
	val = get_env_value(env, var);
	temp = ft_strjoin(result, val);
	free(var);
	free(result);
	return (temp);
}

/*
Adds a single non-variable character to the result string
*/
char	*append_char(char *result, const char *str, int *i)
{
	char	buf[2];
	char	*temp;

	buf[0] = str[*i];
	buf[1] = '\0';
	(*i)++;
	temp = ft_strjoin(result, buf);
	free(result);
	return (temp);
}

char	*expand_dollar_variable(char *str, t_env *env)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			result = append_var_val(result, str, &i, env);
		else
			result = append_char(result, str, &i);
	}
	return (result);
}

int	handle_quotes(char *input, int *i, t_token **tokens, t_env *env)
{
	char	quote;
	int		start;
	char	*quoted;
	char	*expanded;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		quote = input[(*i)++];
		start = *i;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		quoted = ft_strndup(&input[start], *i - start);
		if (quote == '"')
			expanded = expand_dollar_variable(quoted, env);
		else
			expanded = ft_strdup(quoted);
		add_token(tokens, new_token(expanded, TOKEN_WORD));
		free(quoted);
		free(expanded);
		if (input[*i] == quote)
			(*i)++;
		return (1);
	}
	return (0);
}
