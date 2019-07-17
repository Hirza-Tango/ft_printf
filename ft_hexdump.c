/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:02:23 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/17 14:17:08 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hexdump(void *region, size_t size, off_t offset, int fd)
{
	size_t			i;

	i = 0;
	if (!region)
		return ;
	while (i < size)
	{
		ft_printf_fd(fd,
			"%016zx       %02hhx", offset + i, *(char *)(region + i));
		i++;
		while (i < size && i % 16)
			ft_printf_fd(fd, " %02hhx", *(char *)(region + i++));
		ft_putendl("");
	}
}
