/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:51:49 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/11 17:46:54 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_extract_next_line(char **temp)
{
	char	*extr_line;
	char	*rem_txt;

	rem_txt = *temp;
	while (*rem_txt != '\0' && *rem_txt != '\n')
		rem_txt++;
	if (*rem_txt == '\n')
		rem_txt++;
	extr_line = ft_substr (*temp, 0, (size_t)(rem_txt - *temp));
	if (!extr_line)
	{
		free (*temp);
		*temp = NULL;
		return (NULL);
	}
	rem_txt = ft_substr (rem_txt, 0, ft_strlen_gnl(rem_txt));
	free (*temp);
	*temp = rem_txt;
	return (extr_line);
}

static char	*ft_concat_lines(char *temp, int fd, char *buf)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read && !ft_strchr(temp, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			free(temp);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		temp = ft_strjoin_gnl(temp, buf);
		if (!temp)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (temp);
}

static char	*ft_read_upd8(char *temp, int fd, char *buf)
{
	temp = ft_concat_lines(temp, fd, buf);
	if (!temp)
	{
		temp = NULL;
		return (NULL);
	}
	if (!*temp)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buf;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp)
		temp = ft_strdup("");
	if (!temp)
		return (NULL);
	buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		if (temp)
			free (temp);
		temp = NULL;
		return (NULL);
	}
	temp = ft_read_upd8(temp, fd, buf);
	if (!temp)
		return (NULL);
	return (ft_extract_next_line(&temp));
}
