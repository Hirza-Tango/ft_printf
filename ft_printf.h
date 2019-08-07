/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:35:46 by dslogrov          #+#    #+#             */
/*   Updated: 2019/08/07 15:04:05 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <libft.h>
# include <stdarg.h>

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
	long int		width;
	long int		precision;
}				t_printf_args;

int				ft_vprintf_fd(int fd, const char *format, va_list args);
int				ft_printf(const char *format, ...);
int				ft_printf_fd(int fd, const char *format, ...);

char			*ft_getstr_all(t_printf_args *args);
long int		ft_putarg(t_printf_args *a, int fd);
size_t			pad_start(t_printf_args *a, const long int len, int fd);
size_t			pad_end(t_printf_args *a, const long int len, const char *str,
	int fd);

#endif
