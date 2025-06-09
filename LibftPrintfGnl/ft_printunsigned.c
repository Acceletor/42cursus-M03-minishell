/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:33:59 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/02 00:16:46 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunisgned_recursive(unsigned int n, int *len)
{
	char	c;

	if (n >= 10)
		ft_putunisgned_recursive(n / 10, len);
	c = (n % 10) + '0';
	write(1, &c, 1);
	(*len)++;
}

int	ft_printunsigned(unsigned int n)
{
	int	len;

	len = 0;
	ft_putunisgned_recursive(n, &len);
	return (len);
}
