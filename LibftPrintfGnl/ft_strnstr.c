/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:13:57 by eeravci           #+#    #+#             */
/*   Updated: 2024/12/29 18:21:55 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	x;
	size_t	y;

	if (!big && !len)
		return (NULL);
	if (!*little)
		return ((char *)big);
	x = 0;
	y = 0;
	while (big[x] != '\0' && x < len)
	{
		if (big[x] == little[y])
		{
			while (big[x + y] == little[y] && x + y < len)
			{
				if (little[y + 1] == '\0')
					return ((char *)big + x);
				y++;
			}
			y = 0;
		}
		x++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*big;
	char	*little;
	char	*result;

	big = "We're trying to find first occurance of a string";
	little = "e";
	result = ft_strnstr(big, little, 2);
	if (result)
		printf("The string has been found: %s\n", result);
	else
		printf("The string has not been found");
}

*/
