/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 13:43:52 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/17 18:13:54 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main()
{
	printf("%lx", 4294967296);
	printf("$\n");
	ft_printf("%lx", 4294967296);
	printf("$\n");
	return (0);
}
