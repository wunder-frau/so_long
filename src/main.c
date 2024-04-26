#include "../so_long.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		exit(1);
	}
	if (!ends_with_ber(argv[1]))
		write(2, "Error: Invalid file format. Use a .ber file.\n", 45);
	map.data = init(argv[1]);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	map.window = init_window(&map.data);
	draw_background(&map.data, map.window);
	draw_foreground(&map.data, map.window);
	mlx_key_hook(map.window, &key_hook, &map);
	mlx_loop(map.window);
	mlx_close_window(map.window);
	mlx_terminate(map.window);
	return (0);
}
