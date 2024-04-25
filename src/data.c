#include "../so_long.h"

static void	read_line(int fd, int y, t_span *data)
{
	char	*line;
	int		x;

	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("Error: Could not read line %d\n", y + 1);
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
		ft_printf("Error: Map is not rectangular, see line %d\n", y + 1);
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
		ft_printf("Error: Not valid symbol '%c'\n", obj);
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

int	count(const t_span *data, const t_symbol s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < data->nx * data->ny)
	{
		if (data->elems[i] == s)
			count++;
		++i;
	}
	return (count);
}

void	fill(const char *file, t_span *data)
{
	int	fd;
	int	y;

	fd = open_file(file);
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
