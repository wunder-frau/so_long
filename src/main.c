#include "../so_long.h"

//: data.c {{{
t_symbol	convert(const char obj)
{
	switch (obj)
	{
	case 'C':
		return (COLLECTABLE);
	case 'E':
		return (ESCAPE);
	case '1':
		return (OBSTACLE);
	case 'P':
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
//: }}}

//: file.c {{{
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

t_span	init(const char *file)
{
	t_span	data;

	data.nx = get_line_len(file);
	data.ny = count_rows(file);
	data.elems = (t_symbol *) malloc(sizeof(t_symbol) * data.nx * data.ny);
	if (!data.elems)
	{
		ft_printf("Error: memory allocation");
		free(data.elems);
		exit(1);
	}
	fill(file, &data);
	if (count(&data, PLAYER) != 1 || count(&data, ESCAPE) != 1)
	{
		ft_printf("Error: multiple players or escapes found on the data");
		free(data.elems);
		exit(1);
	}
	return (data);
}
//: }}}

//: move.c {{{
bool	is_possible_move(const t_span *data, const int target_ind)
{
	t_symbol	s;

	if (target_ind < 0 || target_ind >= data->nx * data->ny)
		return (false);
	s = data->elems[target_ind];
	if (s == OBSTACLE || (count(data, COLLECTABLE) != 0 && s == ESCAPE))
		return (false);
	return (true);
}

void	move_left(t_span *data)
{
	int	curr;

	curr = find(data, PLAYER);
	if (is_possible_move(data, curr - 1))
	{
		data->elems[curr] = SPACE;
		data->elems[curr - 1] = PLAYER;
	}
}

void	move_right(t_span *data)
{
	int	curr;

	curr = find(data, PLAYER);
	if (is_possible_move(data, curr + 1))
	{
		data->elems[curr] = SPACE;
		data->elems[curr + 1] = PLAYER;
	}
}

void	move_up(t_span *data)
{
	int	curr;

	curr = find(data, PLAYER);
	if (is_possible_move(data, curr - data->nx))
	{
		data->elems[curr] = SPACE;
		data->elems[curr - data->nx] = PLAYER;
	}
}

void	move_down(t_span *data)
{
	int	curr;

	curr = find(data, PLAYER);
	if (is_possible_move(data, curr + data->nx))
	{
		data->elems[curr] = SPACE;
		data->elems[curr + data->nx] = PLAYER;
	}
}
//: }}}

//: draw.c {{{
mlx_t *init_window(const t_span *data)
{
	mlx_t *window = mlx_init(TILE * data->nx, TILE * data->ny, "Map Window", true);
	if (!window)
	{
		ft_printf("Error: Failed to initialise window");
		exit(1);
	}
	return (window);
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

void draw_background(const t_span *data, mlx_t *window)
{
	int			i;
	int			xt;
	int			yt;
	t_symbol	curr;

	i = 0;
	while (i < data->nx * data->ny)
	{
		curr = data->elems[i];
		if (curr == COLLECTABLE || curr == PLAYER)
			curr = SPACE;

		xt = TILE * (i % data->nx);
		yt = TILE * (i / data->nx);
		mlx_image_to_window(window, get_image(window, curr), xt, yt);
		++i;
	}
}

void draw_foreground(const t_span *data, mlx_t *window)
{
	int			i;
	int			xt;
	int			yt;
	t_symbol	curr;

	i = 0;
	while (i < data->nx * data->ny)
	{
		curr = data->elems[i];
		if (curr == COLLECTABLE || curr == PLAYER)
		{
			xt = TILE * (i % data->nx);
			yt = TILE * (i / data->nx);
			mlx_image_to_window(window, get_image(window, curr), xt, yt);
		}
		++i;
	}
}

void	key_hook(mlx_key_data_t keydata, void *args)
{
	t_map	*map;

	map = args;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(map->window);
		return ;
	}

	print(&map->data);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(&map->data);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(&map->data);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(&map->data);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(&map->data);

	ft_printf("count: %d\n", count(&map->data, COLLECTABLE));
	print(&map->data);
}
//: }}}

int	main(int argc, char **argv)
{
	// mlx_t	*window;
	// t_span	data;
	t_map	map;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		exit(1);
	}
	map.data = init(argv[1]);

	ft_printf("%d\n", find(&map.data, PLAYER));
	ft_printf("%d\n", count(&map.data, PLAYER));
	ft_printf("%d\n", count(&map.data, COLLECTABLE));

	map.window = init_window(&map.data);
	draw_background(&map.data, map.window);
	draw_foreground(&map.data, map.window);
	mlx_key_hook(map.window, &key_hook, &map);
	mlx_loop(map.window);
	mlx_close_window(map.window);
	return (0);
}
