/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:10:09 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/01 09:52:33 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_put_digit(int nb)
{
	long		l_nb;
	int			count;
	int			check;

	l_nb = nb;
	count = 0;
	if (l_nb < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		count++;
		l_nb = -1 * l_nb;
	}
	if (l_nb >= 10)
		count += ft_put_digit((l_nb / 10));
	{
		if (count == -1)
			return (-1);
		check = write (1, &FT_BASE10[l_nb % 10], 1);
		if (check == -1)
			return (-1);
		return (++count);
	}
}
