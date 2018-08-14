/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:31:04 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/14 16:41:53 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	return (ft_vprintf_fd(1, format, args));
}

int		ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	return (ft_vprintf_fd(fd, format, args));
}