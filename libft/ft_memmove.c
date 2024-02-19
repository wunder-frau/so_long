/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:20:04 by istasheu          #+#    #+#             */
/*   Updated: 2023/11/14 16:52:55 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*chard;
	char	*chars;

	chard = (char *)dst;
	chars = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst <= src)
	{
		while (len--)
		{
			*chard++ = *chars++;
		}
	}
	else if (dst > src)
	{
		chard += len - 1;
		chars += len - 1;
		while (len--)
		{
			*chard-- = *chars--;
		}
	}
	return (dst);
}
