#include "../so_long.h"

t_symbol	convert(const char obj)
{
	switch (obj)
	{
	case 'C':
		return (collectable);
	case 'E':
		return (escape);
	case '1':
		return (obstacle);
	case 'P':
		return (player);
	case '0':
		return (space);
	default:
		ft_printf("Error: Not valid symbol '%c'\n", obj);
		exit(1);
	}
}

//TODO: bool	is_unique(const t_span *map, const t_symbol s)

int open_file(const char *file) {
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening the file\n", 2);
		perror(file);
	}
	return (fd);
}

/**
 * Calculate first line length.
 */
int get_line_len(const char *file)
{
	int		count;
	int		fd;
	char	c;

	fd = open_file(file);
	count = 0;
	while (read(fd, &c, 1) > 0) {
		if (c == '\n')
			break;
		count++;
	}
	close(fd);
	return (count);
}

int count_rows(const char *file)
{
	int		count;
	int		fd;
	char	c;
	int		eof;

	fd = open_file(file);
	count = 0;
	eof = 0;
	while (read(fd, &c, 1) > 0) {
		if (c == '\n')
			count++;
		else if (c == EOF)
			eof = 1;
	}
	close(fd);
	if (!eof)
		count++;
	return count;
}

void fill(const char *file, t_span *map)
{
	int	fd;
	int	y;
	int	x;

	fd = open_file(file);
	y = 0;
	while (y < map->ny)
	{
		char *line = get_next_line(fd);
		x = 0;
		while (x < map->nx)
		{
			map->data[map->nx * y + x] = convert(line[x]);
			++x;
		}
		free(line);
		++y;
	}
	close(fd);
}

t_span	init(const char *file)
{
	t_span	map;

	map.nx = get_line_len(file);
	map.ny = count_rows(file);
	map.data = (t_symbol *) malloc(sizeof(t_symbol) * map.nx * map.ny);
	if (!map.data)
	{
		ft_printf("Error: memory allocation");
		free(map.data);
		exit(1);
	}
	fill(file, &map);
	/* if (!is_unique(&map, player) || !is_unique(&map, escape))
	{
		ft_printf("Error: multiple players or escapes found on the map");
		free(map.data);
		exit(1);
	} */
	return (map);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage: %s map_file\n", argv[0]);
		exit(1);
	}

	t_span map = init(argv[1]);
	int y = 0;
	while (y < map.ny)
	{
		int x = 0;
		while (x < map.nx)
		{
			ft_printf("%d", map.data[map.nx * y + x]);
			++x;
		}
		ft_printf("\n");
		++y;
	}

	return (0);
}
