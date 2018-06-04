/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:20:14 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/04 17:51:26 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft/libft.h"

int		ft_put_escape(char *c)
{
	if (*c == 'a')
		ft_putchar('\a');
	else if (*c == 'b')
		ft_putchar('\b');
	else if (*c == 'c')
		return (0);
	else if (*c == 'f')
		ft_putchar('\f');
	else if (*c == 'n')
		ft_putchar('\n');
	else if (*c == 'r')
		ft_putchar('\r');
	else if (*c == 't')
		ft_putchar('\t');
	else if (*c == 'v')
		ft_putchar('\v');
	else if (*c == '\'')
		ft_putchar('\'');
	else if (*c == '\\')
		ft_putchar('\\');
	else if (ft_isdigit(*c))
		return (ft_putnbr_base(c, 8));
	return (1);
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	esc_len;
	char	*current;

	current = (char *)format;
	va_start(args, current);
	while (*current)
		if (*current == '\\')
		{
			if (!(esc_len = ft_put_escape(++current)))
				return (0);
			current += esc_len;
		}
		else if (*current == '%')
			current += ft_put_arg((++current), args);
		else
			ft_putchar(*current++);
	return (current - format);
}
