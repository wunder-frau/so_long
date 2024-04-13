#include "../so_long.h"

//: map.c {{{
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

char	*get_path(const t_symbol s)
{
	switch (s)
	{
	case collectable:
		return (TEXTURE_COLLECTABLE);
	case escape:
		return (TEXTURE_EXIT);
	case obstacle:
		return (TEXTURE_WALL);
	case player:
		return (TEXTURE_PLAYER);
	case space:
		return (TEXTURE_FLOOR);
	}
}


//TODO: bool	count(const t_span *map, const t_symbol s)

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
	/* if (count(&map, player) != 1 || count(&map, escape) != 1)
	{
		ft_printf("Error: multiple players or escapes found on the map");
		free(map.data);
		exit(1);
	} */
	return (map);
}
//: }}}

//: draw.c {{{
mlx_t *init_window(const t_span *map)
{
	mlx_t *window = mlx_init(TILE * map->nx, TILE * map->ny, "Map Window", true);
	if (!window)
	{
		ft_printf("Error: Failed to initialise window");
		exit(1);
	}
	return (window);
}

void window_input_hook(void *param) {
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

mlx_image_t	*get_image(mlx_t *window, const t_symbol s)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;

	texture = mlx_load_png(get_path(s));
	image = mlx_texture_to_image(window, texture);
	mlx_delete_texture(texture);
	if (!image)
	{
		ft_printf("Error: Failed to create '%s' texture\n", get_path(s));
		exit(1);
	}
	return (image);
}

void draw_background(const t_span *map, mlx_t *window)
{
	int			i;
	int			xt;
	int			yt;
	t_symbol	curr;

	i = 0;
	while (i < map->nx * map->ny)
	{
		curr = map->data[i];
		if (curr == collectable || curr == player)
			curr = space;

		xt = TILE * (i % map->nx);
		yt = TILE * (i / map->nx);
		mlx_image_to_window(window, get_image(window, curr), xt, yt);
		++i;
	}
}

void draw_foreground(const t_span *map, mlx_t *window)
{
	int			i;
	int			xt;
	int			yt;
	t_symbol	curr;

	i = 0;
	while (i < map->nx * map->ny)
	{
		curr = map->data[i];
		if (curr == collectable || curr == player)
		{
			xt = TILE * (i % map->nx);
			yt = TILE * (i / map->nx);
			mlx_image_to_window(window, get_image(window, curr), xt, yt);
		}
		++i;
	}
}
//: }}}

void print(const t_span map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.ny)
	{
		x = 0;
		while (x < map.nx)
		{
			ft_printf("%d", map.data[map.nx * y + x]);
			++x;
		}
		ft_printf("\n");
		++y;
	}
}

int	main(int argc, char **argv)
{
	mlx_t	*window;
	t_span	map;

	if (argc != 2)
	{
		ft_printf("Usage: %s map_file\n", argv[0]);
		exit(1);
	}

	map = init(argv[1]);
	print(map);

	window = init_window(&map);
	draw_background(&map, window);
	draw_foreground(&map, window);
	if (mlx_loop_hook(window, &window_input_hook, window) == 0)
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	// mlx_key_hook(window, &key_hook, window);
	mlx_loop(window);
	mlx_close_window(window);
	return (0);
}
