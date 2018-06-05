/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:08:39 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/05 15:27:29 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_atou_base(const char *value, unsigned char base)
{
	char			*byte;
	size_t			result;
	int				sign;
	unsigned char	curr;

	byte = (char *)value;
	while (ft_isspace(*byte))
		byte++;
	result = 0;
	while ((curr = ft_isdigit(*byte) ? *byte - '0' : *byte - 'A' + 10))
	{
		if (!ft_isalnum(*byte) || curr >= base)
			break ;
		result = result * 10 + curr;
		byte++;
	}
	return (result);
}
