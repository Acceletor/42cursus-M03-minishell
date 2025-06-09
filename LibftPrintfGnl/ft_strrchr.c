/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:17:34 by eeravci           #+#    #+#             */
/*   Updated: 2024/12/26 17:25:56 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*retvalue;

	retvalue = NULL;
	while (*s)
	{
		if (*s == c)
		{
			retvalue = (char *)s;
		}
		s++;
	}
	if (c == '\0')
	{
		retvalue = (char *)s;
	}
	return (retvalue);
}
