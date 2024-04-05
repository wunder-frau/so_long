/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:15:04 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/01 08:35:52 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr(const char *s)
{
	int	check;

	if (s != NULL)
	{
		check = write (1, s, ft_strlen(s));
		if (check == -1)
			return (-1);
		return (check);
	}
	else
	{
		check = write(1, "(null)", 6);
		if (check == -1)
			return (-1);
		return (6);
	}
}
