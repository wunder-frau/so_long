/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:54:59 by istasheu          #+#    #+#             */
/*   Updated: 2024/04/26 14:55:03 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	read_line(int fd, int y, t_span *data)
{
	char	*line;
	int		x;

	line = get_next_line(fd);
	if (!line)
	{
		ft_putstr_fd("Error\n Could not read line\n", 2);
		close(fd);
		exit(1);
	}
	x = 0;
	while (line[x] != '\n' && line[x])
	{
		if (x < data->nx)
			data->elems[data->nx * y + x] = convert(line[x]);
		++x;
	}
	if (x != data->nx)
	{
		ft_putstr_fd("Error\n Map is not rectangular", 2);
		free(line);
		close(fd);
		exit(1);
	}
	free(line);
}

t_symbol	convert(const char obj)
{
	if (obj == 'C')
		return (COLLECTABLE);
	else if (obj == 'E')
		return (ESCAPE);
	else if (obj == '1')
		return (OBSTACLE);
	else if (obj == 'P')
		return (PLAYER);
	else if (obj == '0')
		return (SPACE);
	else
	{
		ft_putstr_fd("Error\n Not valid symbol\n", 1);
		exit(1);
	}
}

char	*get_path(const t_symbol s)
{
	if (s == COLLECTABLE)
		return (TEXTURE_COLLECTABLE);
	else if (s == ESCAPE)
		return (TEXTURE_EXIT);
	else if (s == OBSTACLE)
		return (TEXTURE_WALL);
	else if (s == PLAYER)
		return (TEXTURE_PLAYER);
	else if (s == SPACE)
		return (TEXTURE_FLOOR);
	else
		return (NULL);
}

void	fill(const char *file, t_span *data)
{
	int	fd;
	int	y;

	fd = safe_open(file);
	y = 0;
	while (y < data->ny)
	{
		read_line(fd, y, data);
		++y;
	}
	close(fd);
}

int	find(const t_span *data, const t_symbol s)
{
	int	i;

	i = 0;
	while (i < data->nx * data->ny)
	{
		if (data->elems[i] == s)
			return (i);
		++i;
	}
	return (-1);
}
