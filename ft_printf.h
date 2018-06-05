/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:35:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/05 18:49:04 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <libft.h>
# include <stdarg.h>

# define MIN(X,Y) X > Y ? Y : X
# define MAX(X,Y) X < Y ? Y : X
# define S_TYPE_0 int
# define S_TYPE_1 char
# define S_TYPE_2 short int
# define S_TYPE_3 long long int
# define S_TYPE_4 long int
# define S_TYPE_5 intmax_t
# define S_TYPE_6 size_t

typedef enum	e_types
{
	INT,
	CHAR,
	SHORT_INT,
	LONG_LONG_INT,
	LONG_INT,
	INTMAX_T,
	SIZE_T
}				t_types;

typedef enum	e_printf_flags
{
	FORCE_STYLE = 1,
	PAD_ZERO = 2,
	LEFT_JUSTIFY = 4,
	SIGN_PLUS = 8,
	SIGN_SPACE = 16
}				t_printf_flags;

typedef struct	s_printf_args
{
	char			format;
	va_list			*args;
	unsigned char	flags;
	size_t			width;
	size_t			precision;
}				t_printf_args;

int				ft_printf(const char format, ...);
size_t			ft_putnbr_base(const char *value, unsigned char base);
size_t			ft_atou_base(const char *value, unsigned char base);

#endif
