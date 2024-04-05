/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 07:58:57 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/01 12:05:00 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_put_unumber(unsigned long n, const char *base)
{
	int				count;
	int				c;
	unsigned long	system;

	system = ft_strlen(base);
	count = 0;
	if (n >= system)
		count = ft_put_unumber(n / system, base);
	if (count == -1)
		return (-1);
	c = write (1, &base[n % system], 1);
	if (c == -1)
		return (-1);
	return (++count);
}
