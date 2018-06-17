/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:29:08 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/17 15:38:23 by dslogrov         ###   ########.fr       */
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
