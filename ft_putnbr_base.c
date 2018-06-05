/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:29:08 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/05 18:00:16 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_putnbr_base(const char *value, unsigned char base)
{
	char *temp;

	ft_putchar((char)ft_atoi_base(value, base));
	temp = (char *)value;
	while ((ft_isdigit(*temp) ? *temp - '0' : *temp - 'A' + 10) < base
		&& ft_isalnum(*temp))
		temp++;
	return (temp - value);
}
