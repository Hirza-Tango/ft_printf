/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 13:43:52 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/17 15:57:28 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main()
{
	printf("%lp", 42);
	printf("$\n");
	ft_printf("%lp", 42);
	printf("$\n");
	return (0);
}