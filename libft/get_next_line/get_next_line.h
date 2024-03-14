/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:44:17 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/11 18:12:38 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen_gnl(const char *str);
// char	*ft_strchr_gnl(const char *s, int c);
// char	*ft_strdup_gnl(const char *s1);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char *s1, char const *s2);
char	*get_next_line(int fd);

#endif
