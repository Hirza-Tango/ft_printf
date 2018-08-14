/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:20:14 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/14 16:33:38 by dslogrov         ###   ########.fr       */
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

static long int			ft_assign_width(char **format, va_list args)
{
	long ret;

	if (**format == '*')
	{
		(*format)++;
		ret = va_arg(args, int);
	}
	else
	{
		ret = ft_atou_base(*format, 10);
		while (ft_isdigit(**format))
			(*format)++;
	}
	return (ret);
}

static long int			ft_format_arg(char **format, va_list args, int fd)
{
	t_printf_args	pf_args;
	long int		result;

	pf_args.flags = ft_assign_flags(format);
	pf_args.width = ft_assign_width(format, args);
	if (**format == '.')
	{
		(*format)++;
		pf_args.precision = ft_assign_width(format, args);
	}
	else
		pf_args.precision = -1;
	pf_args.flags += ft_assign_length(format) << 5;
	pf_args.format = **format;
	(*format)++;
	pf_args.args = (va_list *)args;
	result = ft_putarg(&pf_args, fd);
	if (result == -1)
	{
		(*format)--;
		result++;
	}
	return (result);
}

int						ft_vprintf_fd(int fd, const char *format, va_list args)
{
	size_t	written;
	char	**current;

	if (fd < 0)
		return (-1);
	written = 0;
	current = (char **)&format;
	while (**current)
	{
		if (**current == '%')
		{
			*current += 1;
			written += ft_format_arg(current, args, fd);
		}
		else
		{
			ft_putchar_fd(*((*current)++), fd);
			written++;
		}
	}
	va_end(args);
	return (written);
}
