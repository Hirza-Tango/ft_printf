/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:30:21 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/17 17:34:04 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
static char	*ft_getstr_str(t_printf_args args)
{
	char		*str;
	int			*arr;
	int			*temp;
	size_t		len;
	
	if (args.format == 's' && args.flags >> 5 != LONG_INT)
	{
		if (!(str = va_arg(*args.args, char *)))
			return (ft_strdup("(null)"));
		return (ft_strdup(str));
	}
	if (!(arr = va_arg(*args.args, wchar_t *)))
		return (ft_strdup("(null)"));
	temp = arr;
	len = 0;
	while (*temp++)
		len++;
	str = ft_strnew(len * 4 + 1);
	while (*arr)
	{
		str = ft_appendwchar(*arr, str);
		arr++;
	}
	return ((char *)str);
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

static char	*ft_getstr_u(t_printf_args args, char rad)
{
	const unsigned char len = args.flags << 5;

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
	char	*str;

	str = ft_strnew(5);
	ft_appendwchar(va_arg(*args.args, wchar_t), str);
	return (str);
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
