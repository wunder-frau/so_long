/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:56:22 by istasheu          #+#    #+#             */
/*   Updated: 2023/11/14 16:53:38 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	size_t	i;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	i = 0;
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	while (last > first && ft_strchr(set, s1[last - 1]))
		last--;
	trim = (char *)malloc(sizeof(*s1) * (last - first + 1));
	if (!trim)
		return (NULL);
	while (first < last)
		trim[i++] = s1[first++];
	trim[i] = 0;
	return (trim);
}
