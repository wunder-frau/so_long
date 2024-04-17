#include "../so_long.h"

t_symbol	convert(const char obj)
{
	switch (obj)
	{
	case 'C':
	case 'c':
		return (COLLECTABLE);
	case 'E':
	case 'e':
		return (ESCAPE);
	case '1':
		return (OBSTACLE);
	case 'P':
	case 'p':
		return (PLAYER);
	case '0':
		return (SPACE);
	default:
		ft_printf("Error: Not valid symbol '%c'\n", obj);
		exit(1);
	}
}

char	*get_path(const t_symbol s)
{
	switch (s)
	{
	case COLLECTABLE:
		return (TEXTURE_COLLECTABLE);
	case ESCAPE:
		return (TEXTURE_EXIT);
	case OBSTACLE:
		return (TEXTURE_WALL);
	case PLAYER:
		return (TEXTURE_PLAYER);
	case SPACE:
		return (TEXTURE_FLOOR);
	}
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
	int	x;

	fd = open_file(file);
	y = 0;
	while (y < data->ny)
	{
		char *line = get_next_line(fd);
		x = 0;
		while (x < data->nx)
		{
			data->elems[data->nx * y + x] = convert(line[x]);
			++x;
		}
		free(line);
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

void print(const t_span* data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->ny)
	{
		x = 0;
		while (x < data->nx)
		{
			ft_printf("%d", data->elems[data->nx * y + x]);
			++x;
		}
		ft_printf("\n");
		++y;
	}
}