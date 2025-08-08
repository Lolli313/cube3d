/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:22:43 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_identifier(char c, va_list args)
{
	if (c == '%')
		return (ft_print_c('%'));
	else if (c == 'c')
		return (ft_print_c(va_arg(args, int)));
	else if (c == 's')
		return (ft_print_s(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_print_d(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_u(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_print_x(va_arg(args, unsigned int), c));
	else if (c == 'p')
		return (ft_print_p(va_arg(args, unsigned long long)));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	int		counter;
	int		i;
	va_list	args;

	counter = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			counter += ft_find_identifier(format[i], args);
		}
		else
		{
			write(1, &format[i], 1);
			counter += 1;
		}
		i++;
	}
	return (counter);
}
/*
int	main(void)
{
//	cc -Wall -Wextra -Werror ft_printf.c ft_print_c.c ft_print_s.c ft_print_d.c 
//		ft_print_u.c ft_print_x.c ft_print_p.c src/ft_putnbr_fd.c
//	ft_printf("Hello pisciners!\n");
//	char	c = 't';

//	ft_printf("%i\n", );
	printf(" %i ", ft_printf("\"%d\"", 0));
	printf(" %i ", printf("\"%d\"", 0));
//	printf(" %i ", -9223372036854775808);
//	ft_printf(" %i ", -9223372036854775808);
	ft_printf("%i\n", 2147483647);
	ft_printf("Hello %d pisciners!\n", 42);
	ft_printf("Hello %d %s%c", 42, "pisciners!", '\n');
	ft_printf("%p\n", &c);
	printf("%p\n", &c);
	ft_printf("%u\n", 4294967295);
	ft_printf("%x\n", 0);
	printf("%x\n", 0);
	ft_printf("%x\n", 42);
	printf("%x\n", 42);
	ft_printf("%x\n", 4294967295);
	printf("%lx\n", 4294967295);
	return (0);
}*/