/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:20:14 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/05 16:42:34 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft/libft.h"

static unsigned char	ft_assign_flags(char **format)
{
	unsigned char	flags;

	flags = 0;
	while (**format == '#' || **format == '0' || **format == '-'
		|| **format == '+' || **format == ' ')
	{
		if (**format == '#')
			flags |= 1;
		else if (**format == '0')
			flags |= 2;
		else if (**format == '-')
			flags |= 4;
		else if (**format == '+')
			flags |= 8;
		else if (**format == ' ')
			flags |= 16;
		(*format)++;
	}
	return (flags);
}

static unsigned char	ft_assign_length(char **format)
{
	if (**format == 'h')
	{
		if (*(++(*format)) == 'h')
		{
			(*format)++;
			return (1);
		}
		return (2);
	}
	if (**format == 'l')
	{
		if (*(++(*format)) == 'l')
		{
			(*format)++;
			return (3);
		}
		return (4);
	}
	if (*((*format)++) == 'j')
		return (5);
	if (*(*format - 1) == 'z')
		return (6);
	(*format)--;
	return (0);
}

static char			*ft_format_arg(char *format, va_list args)
{
	unsigned char	flags;
	size_t			width;
	size_t			precision;

	flags = 0;
	width = 0;
	precision = 0;
	if (*format == '%')
		ft_putchar('%');
	flags = ft_assign_flags(&format);
	width = ft_atou_base(*format, 8);
	while (ft_isdigit(*format))
		format++;
	if (*format == '.')
		precision = ft_atou_base(*(++(format)), 8);
	else
		precision = 6;
	while (ft_isdigit(*format))
		format++;
	flags += ft_assign_length(&format) >> 5;
	ft_put_arg(*format, args, flags, width, precision);
	return (++format);
}

static size_t				ft_put_escape(char *c)
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

int						ft_printf(const char format, ...)
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
			{
				va_end(args);
				return (current - format);
			}
			current += esc_len;
		}
		else if (*current == '%')
			current = ft_format_arg(++current, args);
		else
			ft_putchar(*current++);
	va_end(args);
	return (current - format);
}
