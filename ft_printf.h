/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:35:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/06/16 16:54:21 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define MIN(X,Y) (X > Y ? Y : X)
# define MAX(X,Y) (X < Y ? Y : X)

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

int				ft_printf(const char *format, ...);
char			*ft_getstr_all(t_printf_args args);
void			ft_putarg(t_printf_args a);

char			*ft_setwchar4(int i, const char *ret);
size_t			ft_putlitnum(const char *value, unsigned char base);

#endif
