/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:30:21 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/10 17:34:07 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_getstr_str(t_printf_args args)
{
	const char		*str = va_arg(*args.args, char *);
	const size_t	len = ft_strlen(str);
	char			*temp;
	int				chars;

	args.flags &= ~SIGN_PLUS;
	args.flags &= ~SIGN_SPACE;
	args.flags &= ~FORCE_STYLE;
	args.flags &= ~PAD_ZERO;
	if (!args.precision)
		args.precision = len;
	if (args.format = 'S' || args.flags << 5 == LONG_INT)
	{
		temp = str;
		chars = 0;
		while (*temp && chars <= args.precision)
			if (*(temp++) > 127)
				args.precision++;
			else
				chars++;
	}
	return (ft_strdup(str));
}

static char	*ft_getstr_dec(t_printf_args args)
{
	const unsigned char len = args.flags << 5;
	// TODO: get atoi to work with intmax+
	args.flags &= ~FORCE_STYLE;
	if (len == LONG_INT || args.format == 'D')
		return (ft_itoa(va_arg(*args.args, long int)));
	if (len == INT)
		return (ft_itoa(va_arg(*args.args, int)));
	if (len == CHAR)
		return (ft_itoa(va_arg(*args.args, char)));
	if (len == SHORT_INT)
		return (ft_itoa(va_arg(*args.args, short int)));
	if (len == LONG_LONG_INT)
		return (ft_itoa(va_arg(*args.args, long long int)));
	if (len == INTMAX_T)
		return (ft_itoa(va_arg(*args.args, intmax_t)));
	if (len == SIZE_T)
		return (ft_itoa(va_arg(*args.args, size_t)));
	else
		exit(1);
}

static char	*ft_getstr_u(t_printf_args args, unsigned char base)
{
	const unsigned char len = args.flags << 5;

	if (args.format = 'p')
		args.flags &= FORCE_STYLE;
	if (len == LONG_INT || args.format == 'O' || args.format == 'U')
		return (ft_itoa_base(va_arg(*args.args, unsigned long int), base));
	if (len == INT)
		return (ft_itoa_base(va_arg(*args.args, unsigned int), base));
	if (len == CHAR)
		return (ft_itoa_base(va_arg(*args.args, unsigned char), base));
	if (len == SHORT_INT)
		return (ft_itoa_base(va_arg(*args.args, unsigned short int), base));
	if (len == LONG_LONG_INT)
		return (ft_itoa_base(va_arg(*args.args, unsigned long long int), base));
	if (len == INTMAX_T)
		return (ft_itoa_base(va_arg(*args.args, uintmax_t), base));
	if (len == SIZE_T)
		return (ft_itoa_base(va_arg(*args.args, size_t), base));
	else
		exit(1);
}

static char	*ft_getstr_char(t_printf_args args)
{
	const int		i = va_arg(*args.args, int);
	char			*str;

	str = ft_strnew(5);
	if (i < 0)
		return (str);
	else if (i <= 0x7F || args.format == 'c')
		*str = (unsigned char)i;
	//TODO: some fancy bitshift shi(f)t
	else if (i <= 0x7FF)
	{
		*str++ = 0;
		*str++ = 0;
	}
	else if (i <= 0xFFFF)
	{
		*str++ = 0;
		*str++ = 0;
		*str++ = 0;
	}
	else if (i <= 0x10FFFF)
	{
		*str++ = 0;
		*str++ = 0;
		*str++ = 0;
		*str++ = 0;
	}
	return (str);
}

char		*ft_getstr_all(t_printf_args args)
{
	const char f = args.format;

	if (f == 's' || f == 'S')
		return (ft_getstr_str(args));
	if (f == 'c' || f == 'C')
		return (ft_getstr_char(args));
	if (f == 'd' || f == 'D' || f == 'i')
		return (ft_getstr_dec(args));
	if (f == 'u' || f == 'U')
		return (ft_getstr_u(args, 10));
	//TODO: get atoi_base to work with 'x' specifier
	if (f == 'p' || f == 'x' || f == 'X')
		return (ft_getstr_u(args, 16));
	if (f == 'o' || f == 'O')
		return (ft_getstr_u(args, 8));
}
