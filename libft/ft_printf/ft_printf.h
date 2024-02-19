/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:47:41 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/01 08:58:33 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "../../libft/libft.h"

# define FT_BASE10 "0123456789"
# define FT_BASE16_UPPER "0123456789ABCDEF"
# define FT_BASE16_LOWER "0123456789abcdef"

int	ft_putchar(char c);
int	ft_put_percent(void);
int	ft_putstr(const char *s);
int	ft_put_unumber(unsigned long n, const char *base);
int	ft_put_ptr(unsigned long p);
int	ft_put_digit(int nb);
int	ft_printf(const char *format_str, ...);

#endif
