/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:41:52 by istasheu          #+#    #+#             */
/*   Updated: 2023/11/21 10:41:17 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long int	nb;
	int			isneg;
	int			i;

	nb = 0;
	isneg = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (*(str++) == '-')
			isneg = -1;
	}
	while (ft_isdigit(str[i]))
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	nb *= isneg;
	if (!(INT_MIN <= nb && nb <= INT_MAX))
	{
		ft_putstr_fd("Error\n", 2);
		exit (1);
	}
	return (nb);
}
