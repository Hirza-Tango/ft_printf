/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:41:37 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/14 16:29:38 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_putarg_str(t_printf_args *a, const char *str, int fd)
{
	int			len;
	size_t		written;

	written = 0;
	len = MAX(ft_strlen(str), (ft_tolower(a->format) == 'c' ? 1U : 0U));
	if (a->precision < 0 || ft_tolower(a->format) == 'c' || a->format == '%')
		a->precision = len;
	if (!(a->flags & LEFT_JUSTIFY))
		while (a->width-- > MIN(len, a->precision))
		{
			ft_putchar_fd(' ', fd);
			written++;
		}
	write(fd, str, MIN(len, a->precision));
	written += MIN(len, a->precision);
	if (a->flags & LEFT_JUSTIFY)
		while (a->width-- > MIN(len, a->precision))
		{
			ft_putchar_fd(' ', fd);
			written++;
		}
	return (written);
}

static size_t	ft_putarg_u(t_printf_args *a, const char *str, int fd)
{
	const long int	len = ft_strlen(str);
	size_t			written;

	written = 0;
	if (a->flags & FORCE_STYLE && (*str || ft_tolower(a->format) == 'o') &&
		(*str != '0' || a->format == 'p'))
	{
		if (a->format == 'p' || (ft_tolower(a->format) == 'x' && *str
			&& *str != '0'))
			a->width > 0 ? a->width-- && written++ : written++;
		a->width > 0 ? a->width-- && written++ : written++;
	}
	written += pad_start(a, len, fd);
	if (a->flags & FORCE_STYLE && (*str || ft_tolower(a->format) == 'o') &&
		(*str != '0' || a->format == 'p'))
	{
		ft_putchar_fd('0', fd);
		if (a->format == 'X' && *str && *str != '0')
			ft_putchar_fd('X', fd);
		else if (a->format == 'p' || (a->format == 'x' && *str && *str != '0'))
			ft_putchar_fd('x', fd);
	}
	return (written + pad_end(a, len, str, fd));
}

static size_t	ft_putarg_i(t_printf_args *a, const char *str, int fd)
{
	const long int	len = ft_strlen(str);
	size_t			written;

	written = 0;
	if (*str != '-' && (a->flags & SIGN_PLUS || a->flags & SIGN_SPACE)
		&& ++written)
		a->width > 0 ? a->width-- : a->width;
	if (*str == '-')
		a->precision++;
	if (!(a->flags & LEFT_JUSTIFY) & !(a->flags & PAD_ZERO))
		while (a->width-- > MAX(len, a->precision))
		{
			ft_putchar_fd(' ', fd);
			written++;
		}
	if (*str != '-' && (a->flags & SIGN_PLUS))
		ft_putchar_fd('+', fd);
	else if (*str != '-' && (a->flags & SIGN_SPACE))
		ft_putchar_fd(' ', fd);
	else if (*str == '-')
	{
		ft_putchar_fd('-', fd);
		str++;
	}
	return (written + pad_end(a, len, str, fd));
}

long int		ft_putarg(t_printf_args *a, int fd)
{
	char		*str;
	size_t		size;

	if (!(str = ft_getstr_all(a)))
		return (-1);
	if (ft_tolower(a->format) == 'u')
		a->flags &= ~FORCE_STYLE;
	if (a->precision > 0 || a->flags & LEFT_JUSTIFY)
		a->flags &= ~PAD_ZERO;
	if (ft_tolower(a->format) == 's' || ft_tolower(a->format) == 'c' ||
		a->format == '%')
		size = ft_putarg_str(a, str, fd);
	else if (ft_tolower(a->format) == 'u' || ft_tolower(a->format) == 'o' ||
		ft_tolower(a->format) == 'x' || a->format == 'p')
		size = ft_putarg_u(a, str, fd);
	else
		size = ft_putarg_i(a, str, fd);
	free(str);
	return (size);
}
