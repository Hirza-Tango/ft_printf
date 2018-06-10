/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:41:37 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/10 17:19:14 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_putarg(t_printf_args a)
{
	const char		*str = ft_getstr_all(a);
	const size_t	len = ft_strlen(str);

	a.width--;
	if (a.flags & FORCE_STYLE && (a.format == 'p' || a.format == 'x'
		|| a.format == 'X'))
	{
		a.width -= write(1, "0x", 2);
		a.flags &= PAD_ZERO;
	}
	else if (a.flags & FORCE_STYLE && (a.format == 'o' || a.format == 'O'))
	{
		a.width -= write(1, "0", 1);
		a.flags &= PAD_ZERO;
	}
	while (!(a.flags & LEFT_JUSTIFY) && (a.width-- > len || a.precision-- > len) && a.flags & PAD_ZERO)
		ft_putchar('0');
	while (!(a.flags & LEFT_JUSTIFY) && (a.width-- > len || a.precision-- > len))
		ft_putchar(' ');
	//TODO: manage symbols
	//TODO: manage string precision
	ft_putstr(str);
	free(str);
	while (a.flags & LEFT_JUSTIFY && a.width-- > len)
		ft_putchar(' ');
}