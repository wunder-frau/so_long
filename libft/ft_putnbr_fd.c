/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:05:44 by istasheu          #+#    #+#             */
/*   Updated: 2023/11/14 16:47:04 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	l_nb;

	l_nb = n;
	if (l_nb < 0)
	{
		ft_putchar_fd('-', fd);
		l_nb = -1 * l_nb;
	}
	if (l_nb >= 10)
	{
		ft_putnbr_fd(l_nb / 10, fd);
		ft_putnbr_fd(l_nb % 10, fd);
	}
	else
		ft_putchar_fd(l_nb + 48, fd);
}
