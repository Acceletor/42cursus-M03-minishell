/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:20:04 by eeravci           #+#    #+#             */
/*   Updated: 2024/12/29 18:41:44 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	chr;

	str = (unsigned char *)s;
	chr = (unsigned char)c;
	while (n > 0)
	{
		if (*str == chr)
			return ((char *)str);
		str++;
		n--;
	}
	return (NULL);
}

/*
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	target;

	str = (unisgned char *)s;
	target = (unsigned char)c;
	while(n > 0)
	{
		if(*str == target)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}

int	main(void)
{
	const char	str[] = "Welcome to Poland";
	const char	ch = 't';
	char		*result;

	result = (char *)ft_memchr(str, ch, ft_strlen(str));
	if (result != NULL)
	{
		printf("'%c' found at position %ld\n", ch, result - str);
	}
	else
	{
		printf("'%c' not found in the string\n", ch);
	}
	return (0);
}
*/
