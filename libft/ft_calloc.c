/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:13:09 by istasheu          #+#    #+#             */
/*   Updated: 2023/11/15 13:01:17 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*dest;
	size_t			total;

	total = -1;
	if (count != 0 && total / count < size)
		return (NULL);
	total = count * size;
	dest = malloc(total);
	if (dest == NULL)
		return (NULL);
	ft_memset(dest, 0, total);
	return (dest);
}
