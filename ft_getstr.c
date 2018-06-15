/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:30:21 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/14 16:37:14 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_getstr_str(t_printf_args args)
{
	const char		*str = va_arg(*args.args, char *);

	args.flags &= ~SIGN_PLUS;
	args.flags &= ~SIGN_SPACE;
	args.flags &= ~FORCE_STYLE;
	args.flags &= ~PAD_ZERO;
	return (ft_strdup(str));
}

static char	*ft_getstr_dec(t_printf_args args)
{
	const unsigned char len = args.flags << 5;
	args.flags &= ~FORCE_STYLE;
	if (len == LONG_INT || args.format == 'D')
		return (ft_itoa(va_arg(*args.args, long int)));
	if (len == INT)
		return (ft_itoa(va_arg(*args.args, int)));
	if (len == CHAR)
		return (ft_itoa((char)va_arg(*args.args, int)));
	if (len == SHORT_INT)
		return (ft_itoa((short int)va_arg(*args.args, int)));
	if (len == LONG_LONG_INT)
		return (ft_itoa(va_arg(*args.args, long long int)));
	if (len == INTMAX_T)
		return (ft_itoa(va_arg(*args.args, intmax_t)));
	if (len == SIZE_T)
		return (ft_itoa(va_arg(*args.args, size_t)));
	else
		exit(1);
}

static char	*ft_getstr_u(t_printf_args args, unsigned char rad)
{
	const unsigned char len = args.flags << 5;

	if (args.format == 'p')
		args.flags &= FORCE_STYLE;
	if (ft_tolower(args.format) == 'u')
		args.flags |= ~FORCE_STYLE;
	if (len == LONG_INT || args.format == 'O' || args.format == 'U')
		return (ft_itoa_base(va_arg(*args.args, unsigned long int), rad));
	if (len == INT)
		return (ft_itoa_base(va_arg(*args.args, unsigned int), rad));
	if (len == CHAR)
		return (ft_itoa_base((unsigned char)va_arg(*args.args, int), rad));
	if (len == SHORT_INT)
		return (ft_itoa_base((unsigned short int)va_arg(*args.args, int), rad));
	if (len == LONG_LONG_INT)
		return (ft_itoa_base(va_arg(*args.args, unsigned long long int), rad));
	if (len == INTMAX_T)
		return (ft_itoa_base(va_arg(*args.args, uintmax_t), rad));
	if (len == SIZE_T)
		return (ft_itoa_base(va_arg(*args.args, size_t), rad));
	else
		exit(1);
}

static char	*ft_getstr_char(t_printf_args args)
{
	const int	i = va_arg(*args.args, int);
	const char	*ret = ft_strnew(5);
	char		*str;

	str = (char *)ret;
	if (i < 0)
		return (str);
	else if (i <= 0x7F || (args.format == 'c' && args.flags << 5 != LONG_INT))
		*str = (unsigned char)i;
	else if (i <= 0x7FF)
	{
		*str++ = 0xC0 | (i >> 6 & 0x1F);
		*str++ = 0x80 | (i & 0x3F);
	}
	else if (i <= 0xFFFF)
	{
		*str++ = 0xE0 | (i >> 12 & 0xF);
		*str++ = 0x80 | (i >> 6 & 0x3F);
		*str++ = 0x80 | (i & 0x3F);
	}
	else if (i <= 0x10FFFF)
		ft_setwchar4(i, ret);
	return ((char *)ret);
}

char		*ft_getstr_all(t_printf_args args)
{
	const char f = args.format;
	
	if (args.precision)
		args.flags |= ~PAD_ZERO;
	if (f == 's' || f == 'S')
		return (ft_getstr_str(args));
	if (f == 'c' || f == 'C')
		return (ft_getstr_char(args));
	if (f == 'd' || f == 'D' || f == 'i')
		return (ft_getstr_dec(args));
	if (f == 'u' || f == 'U')
		return (ft_getstr_u(args, 10));
	if (f == 'X')
		return (ft_getstr_u(args, 16));
	if (f == 'p' || f == 'x')
		return (ft_getstr_u(args, -16));
	if (f == 'o' || f == 'O')
		return (ft_getstr_u(args, 8));
	return (NULL);
}
