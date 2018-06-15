/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:20:14 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/14 17:45:21 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned char	ft_assign_flags(char **format)
{
	unsigned char	flags;

	flags = 0;
	while (**format == '#' || **format == '0' || **format == '-'
		|| **format == '+' || **format == ' ')
	{
		if (**format == '#')
			flags |= FORCE_STYLE;
		else if (**format == '0')
			flags |= PAD_ZERO;
		else if (**format == '-')
			flags |= LEFT_JUSTIFY;
		else if (**format == '+')
			flags |= SIGN_PLUS;
		else if (**format == ' ')
			flags |= SIGN_SPACE;
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
			return (CHAR);
		}
		return (SHORT_INT);
	}
	if (**format == 'l')
	{
		if (*(++(*format)) == 'l')
		{
			(*format)++;
			return (LONG_LONG_INT);
		}
		return (LONG_INT);
	}
	if (*((*format)++) == 'j')
		return (INTMAX_T);
	if (*(*format - 1) == 'z')
		return (SIZE_T);
	(*format)--;
	return (INT);
}

static int				ft_format_arg(char *format, va_list args)
{
	t_printf_args	pf_args;
	const char		*start = format;

	if (*format == '%')
	{
		ft_putchar('%');
		return (1);
	}
	pf_args.flags = ft_assign_flags(&format);
	pf_args.width = ft_atou_base(format, 8);
	while (ft_isdigit(*format))
		format++;
	if (*format == '.')
		pf_args.precision = ft_atou_base((++(format)), 8);
	while (ft_isdigit(*format))
		format++;
	pf_args.flags += ft_assign_length(&format) >> 5;
	pf_args.format = *format;
	pf_args.args = (va_list *)args;
	ft_putarg(pf_args);
	return (++format - start);
}

static size_t			ft_put_escape(char *c)
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
		return (ft_putlitnum(c, 8));
	return (1);
}

int						ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	esc_len;
	char	*current;

	current = (char *)format;
	va_start(args, format);
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
			current += ft_format_arg(current, args) + 1;
		else
			ft_putchar(*current++);
	va_end(args);
	return (current - format);
}
