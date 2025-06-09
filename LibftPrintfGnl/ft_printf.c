/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:33:45 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/02 00:16:00 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_format(va_list args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_length += ft_printstring(va_arg(args, char *));
	else if (format == 'p')
		print_length += ft_printptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		print_length += ft_printnumber(va_arg(args, int));
	else if (format == 'u')
		print_length += ft_printunsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_printhex(va_arg(args, unsigned int), format);
	else if (format == '%')
		print_length += ft_printpercent();
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_length += ft_format(args, str[i + 1]);
			i++;
		}
		else
			print_length += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (print_length);
}

// It's better to write your own main function. :-)
/*
int	main(void)
{
	int				i;
	char			*str;
	unsigned int	u;

	int n, n2;
	i = 'e';
	str = "Cześć!";
	n = 50;
	n2 = -14;
	u = 255;
	// ft_printf("%c\n", i);
	// ft_printf("%s\n", str);
	// ft_printf("%d\n%i\n", n, n2);
	// ft_printf("%p\n", 15);
	// ft_printf("%u\n", u);
	//ft_printf("%X", u);
}*/
