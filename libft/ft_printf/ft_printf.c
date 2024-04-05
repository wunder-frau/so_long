/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:32:03 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/01 08:58:17 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_handle_spec(const char input_val, va_list args)
{
	if (input_val == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (input_val == '%')
		return (ft_put_percent());
	else if (input_val == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (input_val == 'x')
		return (ft_put_unumber(va_arg(args, unsigned int), FT_BASE16_LOWER));
	else if (input_val == 'X')
		return (ft_put_unumber(va_arg(args, unsigned int), FT_BASE16_UPPER));
	else if (input_val == 'p')
		return (ft_put_ptr(va_arg(args, unsigned long)));
	else if (input_val == 'i' || input_val == 'd')
		return (ft_put_digit(va_arg(args, int)));
	else if (input_val == 'u')
		return (ft_put_unumber(va_arg(args, unsigned int), FT_BASE10));
	return (-1);
}

static int	ft_form(const char *f_s, va_list args)
{
	int	len;
	int	len_temp;

	len = 0;
	while (*f_s)
	{
		if (*f_s == '%')
		{
			++f_s;
			len_temp = ft_handle_spec(*f_s, args);
			if (len_temp < 0)
				return (-1);
			len += len_temp;
		}
		else
		{
			if (ft_putchar(*f_s) < 0)
				return (-1);
			len++;
		}
		f_s++;
	}
	return (len);
}

int	ft_printf(const char *f_s, ...)
{
	va_list	args;
	int		len;

	va_start(args, f_s);
	len = ft_form(f_s, args);
	va_end(args);
	return (len);
}
