/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:54:34 by istasheu          #+#    #+#             */
/*   Updated: 2023/11/14 16:26:28 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;

	if (needle[0] == '\0')
		return ((char *)haystack);
	if (*needle == '\0')
		return ((char *)needle);
	if (!len)
		return (NULL);
	n = ft_strlen(needle);
	while (*haystack != '\0' && len-- >= n)
	{
		if (haystack && needle && *haystack == *needle
			&& ft_strncmp(haystack, needle, n) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
