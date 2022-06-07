/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:19:48 by pfrances          #+#    #+#             */
/*   Updated: 2022/06/07 22:48:52 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_an_option(char c)
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

void	do_repartition(va_list args, size_t *result, size_t *last_pos, char c)
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
		*result += write(STDOUT_FILENO, "0x", 2);
		*result += print_nbr((long)va_arg(args, unsigned long), HEXA_BASE_LOW);
	}
	else if (c == '%')
		*result += write(STDOUT_FILENO, "%%", 1);
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
				do_repartition(args, &result, &last_pos, str[i + 1]);
		}
		if (str[i + 1] == '\0')
			result += write(STDOUT_FILENO, str + last_pos, i - last_pos + 1);
		i++;
	}
	va_end(args);
	return ((int)result);
}
