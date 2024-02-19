/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:45:37 by istasheu          #+#    #+#             */
/*   Updated: 2023/11/14 16:20:30 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*k;

	k = (unsigned char *)s;
	while (n)
	{
		if (*k == (unsigned char)c)
		{
			return (k);
		}
		if (n)
			k++;
		n--;
	}
	return (0);
}
