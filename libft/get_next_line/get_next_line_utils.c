/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:30:59 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/12 08:56:50 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	const char	*p;

	p = str;
	while (*p)
		p++;
	return ((size_t)(p - str));
}

char	*ft_strjoin_gnl(char *b_s, char const *a_s)
{
	char	*r_s;
	char	*r_p;
	char	*b_p;

	if (b_s == NULL)
		return (ft_strdup(a_s));
	r_s = malloc(sizeof(*r_s) * (ft_strlen_gnl(b_s) + ft_strlen_gnl(a_s) + 1));
	if (!r_s)
	{
		free(b_s);
		return (NULL);
	}
	b_p = b_s;
	r_p = r_s;
	while (*b_p)
		*r_p++ = *b_p++;
	while (*a_s)
		*r_p++ = *a_s++;
	*r_p = '\0';
	free(b_s);
	return (r_s);
}
