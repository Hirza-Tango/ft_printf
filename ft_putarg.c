/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:41:37 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/18 18:20:25 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_putarg_str(t_printf_args a, const char *str)
{
	const long int	len = ft_strlen(str);
	size_t			written;

	written = 0;
	if (a.precision <= 0 || ft_tolower(a.format) == 'c' || a.format == '%')
		a.precision = len;
	if (ft_strequ(str, "^@"))
	{
		a.width++;
		written--;
	}
	if (!(a.flags & LEFT_JUSTIFY))
		while (a.width-- > MIN(len, a.precision))
		{
			ft_putchar(' ');
			written++;
		}
	write(1, str, MIN(len, a.precision));
	written += MIN(len, a.precision);
	if (a.flags & LEFT_JUSTIFY)
		while (a.width-- > MIN(len, a.precision))
		{
			ft_putchar(' ');
			written++;
		}
	return (written);
}

static size_t	ft_putarg_u(t_printf_args a, const char *str)
{
	const long int	len = ft_strlen(str);
	size_t			written;

	written = 0;
	if (a.flags & FORCE_STYLE)
	{
		a.width > 0 ? a.width-- : a.width;
		written++;
		if (a.format == 'p' || ft_tolower(a.format) == 'x')
		{
			a.width > 0 ? a.width-- : a.width;
			written++;
		}
	}
	if (!(a.flags & LEFT_JUSTIFY) & !(a.flags & PAD_ZERO))
		while (a.width-- > MAX(len, a.precision))
		{
			written++;
			ft_putchar(' ');
		}
	if (a.flags & FORCE_STYLE)
	{
		ft_putchar('0');
		if (a.format == 'X')
			ft_putchar('X');
		else if (a.format == 'p' || a.format == 'x')
			ft_putchar('x');
	}
	while (!(a.flags & LEFT_JUSTIFY) && a.flags & PAD_ZERO && a.width-- > len)
	{
		ft_putchar('0');
		written++;
	}
	ft_putstr(str);
	written += len;
	if (a.flags & LEFT_JUSTIFY)
		while (a.width-- > MAX(len, a.precision))
		{
			ft_putchar(' ');
			written++;
		}
	return (written);
}

static size_t	ft_putarg_i(t_printf_args a, const char *str)
{
	const long int	len = ft_strlen(str);
	size_t			written;

	written = 0;
	if (*str != '-' && (a.flags & SIGN_PLUS || a.flags & SIGN_SPACE))
	{
		a.width > 0 ? a.width-- : a.width;
		written++;
	}
	if (!(a.flags & LEFT_JUSTIFY) & !(a.flags & PAD_ZERO))
		while (a.width-- > MAX(len, a.precision))
		{
			ft_putchar(' ');
			written++;
		}
	if (*str != '-' && (a.flags & SIGN_PLUS))
		ft_putchar('+');
	else if (*str != '-' && (a.flags & SIGN_SPACE))
		ft_putchar(' ');
	else if (*str == '-')
		{
			ft_putchar('-');
			str++;
		}
	while (!(a.flags & LEFT_JUSTIFY) && a.flags & PAD_ZERO && a.width-- > len)
	{
		ft_putchar('0');
		written++;
	}
	ft_putstr(str);
	written += len;
	if (a.flags & LEFT_JUSTIFY)
		while (a.width-- > MAX(len, a.precision))
		{
			ft_putchar(' ');
			written++;
		}
	return (written);
}
#include <stdio.h>
long int		ft_putarg(t_printf_args a)
{
	char		*str;
	
	if (!(str = ft_getstr_all(a)))
		return (-1);
	if (ft_tolower(a.format) == 'u' || !*str || *str == '0')
		a.flags &= ~FORCE_STYLE;
	if (ft_tolower(a.format) == 's' || ft_tolower(a.format) == 'c' ||
		a.format == '%')
		return (ft_putarg_str(a, str));
	else if (ft_tolower(a.format) == 'u' || ft_tolower(a.format) == 'o' ||
		ft_tolower(a.format) == 'x' || a.format == 'p')
		return (ft_putarg_u(a, str));
	else
		return (ft_putarg_i(a, str));
	free(str);
}
