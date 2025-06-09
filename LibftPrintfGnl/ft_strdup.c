/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <enes.nev@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:15:02 by eeravci           #+#    #+#             */
/*   Updated: 2024/12/19 11:34:09 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*dest;

	len = ft_strlen(str);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/*
char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(str);
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	while (*str)
	{
		*dest = *str;
		str++;
	}
	*dest = '\0';
	return (dest);
}
*/
/*
int	main(void)
{
	char	*str;
	char	*new;

	str = "Hello world!";
	new = ft_strdup(str);
	printf("%s\n", new);
	free(new);
}
*/
