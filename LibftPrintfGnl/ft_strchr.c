/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:06:27 by eeravci           #+#    #+#             */
/*   Updated: 2024/12/14 14:03:50 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}
/*
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	if (c == '\0')
	{
		while (s[i] != '\0')
			i++;
		return (ptr + i);
	}
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (ptr + i);
		}
		i++;
	}
	return (NULL);
}

int	main(void)
{
	const char	*str = "Merhaba, Dunya";
	char		target;
	char		*result;

	target = 'a';
	result = ft_strchr(str, target);
	if (result)
		printf("Found charachter '%c' at position %s\n", target, result);
	else
		printf("Character not found");
}
*/