#include "../so_long.h"

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
