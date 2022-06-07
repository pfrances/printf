/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:19:48 by pfrances          #+#    #+#             */
/*   Updated: 2022/06/07 23:44:05 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_an_option(char c)
{
	size_t	i;

	i = 0;
	while (OPTION[i] != '\0')
	{
		if (OPTION[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	distribute(va_list args, size_t *result, size_t *last_pos, char c)
{
	if (c == 'c')
		*result += print_c(va_arg(args, int));
	else if (c == 's')
		*result += print_s(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		*result += print_nbr((long)va_arg(args, int), DECIMAL_BASE);
	else if (c == 'u')
		*result += print_nbr((long)va_arg(args, unsigned long), DECIMAL_BASE);
	else if (c == 'x')
		*result += print_nbr((long)va_arg(args, unsigned long), HEXA_BASE_LOW);
	else if (c == 'X')
		*result += print_nbr((long)va_arg(args, unsigned long), HEXA_BASE_UP);
	else if (c == 'p')
	{
		*result += write(1, "0x", 2);
		*result += print_nbr((long)va_arg(args, unsigned long), HEXA_BASE_LOW);
	}
	else if (c == '%')
		*result += write(1, "%%", 1);
	*last_pos += 2;
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	size_t	last_pos;
	size_t	result;

	va_start(args, str);
	i = 0;
	result = 0;
	last_pos = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			result += write(1, str + last_pos, i - last_pos);
			last_pos = i;
			if (is_an_option(str[i + 1]) == TRUE)
				distribute(args, &result, &last_pos, str[i + 1]);
		}
		if (str[i + 1] == '\0')
			result += write(1, str + last_pos, i - last_pos + 1);
		i++;
	}
	va_end(args);
	return ((int)result);
}

//////////////////////////////////////////////////////////////
/*							MAIN							*/
/*
int	main(void)
{
	char			c = 'A';
	char			*s = "hello";
	void			*p = &s;
	int				d = 10;
	int				i = -5;
	unsigned int	u = 123;
	int				x = 42;
	int				X = 150;

	// setvbuf(stdin, NULL, _IONBF, 0);

	// printf("printf : %d\n\n",
	// 	printf("c %c\ns %s\np %p\nd %d\ni %i\nu %u\nx %x\nX %X\n%%\n",
	// 	c, s, p, d, i, u , x , X));

	// setvbuf(stdin, NULL, _IONBF, 0);

	// printf("ft_printf : %d\n",
	// 	ft_printf("c %c\ns %s\np %p\nd %d\ni %i\nu %u\nx %x\nX %X\n%%\n",
	// 	c, s, p, d, i, u , x , X));



	char *s2 = "This is a string     ";
	setvbuf(stdin, NULL, _IONBF, 0);

	printf("%d\n", printf("%s", ""));
	printf("%d\n", printf(" %s", ""));
	printf("%d\n", printf("%s ", ""));
	printf("%d\n", printf(" %s ", ""));
	printf("%d\n", printf(" %s ", "-"));
	printf("%d\n", printf(" %s %s ", "", "-"));
	printf("%d\n", printf(" %s %s ", " - ", ""));
	printf("%d\n", printf(" %s %s %s %s %s", " - ", "", "4", "", s2));
	printf("%d\n", printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 "));
	printf("%d\n", printf(" NULL %s NULL ", NULL));

	setvbuf(stdin, NULL, _IONBF, 0);

	printf("%d\n", ft_printf("%s", ""));
	printf("%d\n", ft_printf(" %s", ""));
	printf("%d\n", ft_printf("%s ", ""));
	printf("%d\n", ft_printf(" %s ", ""));
	printf("%d\n", ft_printf(" %s ", "-"));
	printf("%d\n", ft_printf(" %s %s ", "", "-"));
	printf("%d\n", ft_printf(" %s %s ", " - ", ""));
	printf("%d\n", ft_printf(" %s %s %s %s %s", " - ", "", "4", "", s2));
	printf("%d\n", ft_printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 "));
	printf("%d\n", ft_printf(" NULL %s NULL ", NULL));
	return (0);
}
*/