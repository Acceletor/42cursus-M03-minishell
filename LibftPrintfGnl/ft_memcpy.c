/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:43 by eeravci           #+#    #+#             */
/*   Updated: 2024/12/29 18:20:36 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest != src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	dest[25];
	char	src[] = "Hello my name is Enes.";

	printf ("Before ft_memcpy()\nsrc: %s\ndest: %s\n", src, dest);
	ft_memcpy(dest, src, sizeof(src));
	printf ("After ft_memcpy()\nsrc: %s\ndest: %s\n", src, dest);
}
*/
