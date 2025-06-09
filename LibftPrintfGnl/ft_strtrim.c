/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:10:06 by eeravci           #+#    #+#             */
/*   Updated: 2024/12/21 17:12:35 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed_str;

	trimmed_str = NULL;
	if (s1 != NULL && set != NULL)
	{
		start = 0;
		end = ft_strlen(s1) - 1;
		len = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (end > start && ft_strchr(set, s1[end]))
			end--;
		len = end - start + 1;
		trimmed_str = (char *)malloc(sizeof(char) * (len + 1));
		if (trimmed_str)
		{
			ft_strlcpy(trimmed_str, &s1[start], len + 1);
		}
		return (trimmed_str);
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*str;
	char	*set;
	char	*result;

	str = "    Welcome to Poland! ";
	set = " !";
	result = ft_strtrim(str, set);
	printf("%s\n", result);
	free(result);
}
*/
