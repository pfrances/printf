/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:36:52 by pfrances          #+#    #+#             */
/*   Updated: 2022/06/07 23:16:50 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_c(char c)
{
	return (write(1, &c, 1));
}

size_t	print_s(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

size_t	print_nbr(long nb, char *base)
{
	unsigned long	ulong_nb;
	unsigned long	divisor;
	unsigned long	base_len;
	size_t			i;
	char			buff[65];

	i = 0;
	if (nb < 0)
	{
		ulong_nb = (unsigned long)(-nb);
		buff[i++] = '-';
	}
	else
		ulong_nb = (unsigned long)nb;
	base_len = ft_strlen(base);
	divisor = 1;
	while (ulong_nb / divisor >= base_len)
		divisor *= base_len;
	while (divisor > 0)
	{
		buff[i++] = base[ulong_nb / divisor];
		ulong_nb %= divisor;
		divisor /= base_len;
	}
	return (write(1, buff, i));
}
