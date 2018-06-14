/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:41:37 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/14 16:16:21 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putarg_str(t_printf_args a, const char *str)
{
	const size_t	len = ft_strlen(str);

	if (!a.precision || ft_tolower(a.format) == 'c')
		a.precision = len;
	if (!(a.flags & LEFT_JUSTIFY))
		while (a.width-- > min(len, a.precision))
			ft_putchar(' ');
	ft_putstr(str);
	if (a.flags & LEFT_JUSTIFY)
		while (a.width-- > min(len, a.precision))
			ft_putchar(' ');
}

static void	ft_putarg_u(t_printf_args a, const char *str)
{
	const size_t	len = ft_strlen(str);
	
	if (a.flags & FORCE_STYLE && ft_tolower(a.format) != 'u')
	{
		a.width--;
		if (a.format == 'p' || ft_tolower(a.format == 'x'))
			a.width--;
	}
	if (!(a.flags & LEFT_JUSTIFY) & !(a.flags & PAD_ZERO))
		while (a.width-- > max(len, a.precision))
			ft_putchar(' ');
	if (a.flags & FORCE_STYLE && ft_tolower(a.format) != 'u')
	{
		ft_putchar('0');
		if (a.format == 'X')
			ft_putchar('X');
		else if (a.format == 'p' || a.format == 'x')
			ft_putchar('x');
	}
	while (!(a.flags & LEFT_JUSTIFY) && a.flags & PAD_ZERO && a.width-- > len)
		ft_putchar('0');
	ft_putstr(str);
	if (a.flags & LEFT_JUSTIFY)
		while (a.width-- > max(len, a.precision))
			ft_putchar(' ');
}

static void	ft_putarg_i(t_printf_args a, const char *str)
{
	const size_t	len = ft_strlen(str);
	
	if (*str != '-' && (a.flags & SIGN_PLUS || a.flags & SIGN_SPACE))
		a.width--;
	if (!(a.flags & LEFT_JUSTIFY) & !(a.flags & PAD_ZERO))
		while (a.width-- > max(len, a.precision))
			ft_putchar(' ');
	while (!(a.flags & LEFT_JUSTIFY) && a.flags & PAD_ZERO && a.width-- > len)
		ft_putchar('0');
	if (*str != '-' && (a.flags & SIGN_PLUS))
		ft_putchar('+');
	else if (*str != '-' && (a.flags & SIGN_SPACE))
		ft_putchar(' ');
	ft_putstr(str);
	if (a.flags & LEFT_JUSTIFY)
		while (a.width-- > max(len, a.precision))
			ft_putchar(' ');
}

void			ft_putarg(t_printf_args a)
{
	const char		*str = ft_getstr_all(a);
	const size_t	len = ft_strlen(str);

	a.width--;
	if (ft_tolower(a.format) == 's' || ft_tolower(a.format) == 'c')
		ft_putarg_str(a, str);
	else if (ft_tolower(a.format) == 'u' || ft_tolower(a.format) == 'o' ||
		ft_tolower(a.format) == 'x' || a.format == 'p')
		ft_putarg_u(a, str);
	else
		ft_putarg_i(a, str);
	free(str);
}
