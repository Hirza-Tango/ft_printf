/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:29:08 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/14 16:46:44 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

size_t	ft_putlitnum(const char *value, unsigned char base)
{
	char *temp;

	ft_putchar((char)ft_atou_base(value, base));
	temp = (char *)value;
	while ((ft_isdigit(*temp) ? *temp - '0' : *temp - 'A' + 10) < base
		&& ft_isalnum(*temp))
		temp++;
	return (temp - value);
}

char	*ft_setwchar4(int i, const char *ret)
{
	char	*str;

	str = (char *)ret;
	*str++ = 0xF0 | (i >> 18 & 0x7);
	*str++ = 0x80 | (i >> 12 & 0x3F);
	*str++ = 0x80 | (i >> 6 & 0x3F);
	*str++ = 0x80 | (i & 0x3F);
	return ((char *)ret);
}
