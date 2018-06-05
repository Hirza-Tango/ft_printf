/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:30:21 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/05 18:50:26 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putf_str(t_printf_args pf_args)
{
	const char		*str = va_arg(*pf_args.args, char *);
	const size_t	len = ft_strlen(str);
	char			*temp;
	int				chars;

	if (!pf_args.precision)
		pf_args.precision = len;
	else if (pf_args.format = 'S' || pf_args.flags << 5 == LONG_INT)
	{
		temp = str;
		chars = 0;
		while (*temp && chars <= pf_args.precision)
			if (*(temp++) > 127)
				pf_args.precision++;
			else
				chars++;
	}
	while (pf_args.flags & LEFT_JUSTIFY && pf_args.width-- > len)
		ft_putchar(' ');
	write(1, str, MIN(len, pf_args.precision));
	while (!(pf_args.flags & LEFT_JUSTIFY) && pf_args.width-- > len)
		ft_putchar(' ');
}

void	ft_putf_dec(t_printf_args pf_args)
{
	
}

void	ft_put_arg(t_printf_args pf_args)
{
	if (pf_args.format == 's' || pf_args.format == 'S')
		ft_putf_str(pf_args);
	if (pf_args.format == 'd' || pf_args.format == 'D' || pf_args.format == 'i')
		ft_putf_dec(pf_args);
}
