/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:26:40 by eeravci           #+#    #+#             */
/*   Updated: 2024/12/18 13:59:32 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*arr;

	arr = (unsigned char *)s;
	while (n > 0)
	{
		*arr = (unsigned char)c;
		arr++;
		n--;
	}
	return (s);
}
/*
int	main(void)
{
	char	str[22] = "hello my name is enes";

	printf("befor memset: %s\n", str);
	ft_memset(str, 'a', 5 * sizeof(char));
	printf("after memset: %s\n", str);
}
*/