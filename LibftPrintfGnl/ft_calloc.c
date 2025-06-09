/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:20:36 by eeravci           #+#    #+#             */
/*   Updated: 2024/12/26 17:31:51 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*addr;

	if (nitems == 0 || size == 0)
	{
		nitems = 1;
		size = 1;
	}
	addr = malloc(nitems * size);
	if (!addr)
	{
		return (NULL);
	}
	ft_bzero(addr, size * nitems);
	return (addr);
}
/*
int	main(void)
{
	int	*arr;

	size_t count, size;
	count = 10;
	size = sizeof(int);
	arr = (int *)ft_calloc(count, size);
	if (arr != NULL)
		for (size_t i = 0; i < count; i++)
		{
			printf("arr[%zu = %d\n", i, arr[i]);
		}
	else
	{
		printf("Allocation failed.\n");
	}
}
*/
