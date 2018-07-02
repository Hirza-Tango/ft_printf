/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 15:00:55 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/02 15:12:11 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

size_t	pad_start(t_printf_args *a, const long int len)
{
	size_t	written;

	written = 0;
	if (!(a->flags & LEFT_JUSTIFY) & !(a->flags & PAD_ZERO))
		while (a->width-- > MAX(len, a->precision))
		{
			written++;
			ft_putchar(' ');
		}
	return (written);
}

size_t	pad_end(t_printf_args *a, const long int len, const char *str)
{
	size_t	written;

	written = 0;
	while ((a->flags & PAD_ZERO && a->width > len) || a->precision-- > len)
	{
		ft_putchar('0');
		written++;
		a->width > 0 ? a->width-- : a->width;
	}
	ft_putstr(str);
	written += len;
	if (a->flags & LEFT_JUSTIFY)
		while (a->width-- > MAX(len, a->precision))
		{
			ft_putchar(' ');
			written++;
		}
	return (written);
}
