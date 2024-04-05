/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:42:48 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/01 09:18:59 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_put_ptr(unsigned long p)
{
	int	count;
	int	check;

	count = 0;
	check = write(1, "0x", 2);
	if (check == -1)
		return (-1);
	count = (check + ft_put_unumber(p, FT_BASE16_LOWER));
	if (count == -1)
		return (-1);
	return (count);
}
