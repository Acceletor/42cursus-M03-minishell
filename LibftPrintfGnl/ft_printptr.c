/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:07:48 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/02 00:16:40 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putptr_recursive(unsigned long long n, int *len)
{
	char	c;

	if (n >= 16)
		ft_putptr_recursive(n / 16, len);
	c = "0123456789abcdef"[n % 16];
	write(1, &c, 1);
	(*len)++;
}

int	ft_printptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	len += 2;
	ft_putptr_recursive(ptr, &len);
	return (len);
}
