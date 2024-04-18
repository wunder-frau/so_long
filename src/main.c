#include "../so_long.h"

bool	ends_with_ber(const char *str) {
    size_t len = ft_strlen(str);
	ft_printf("%d\n", len);
	ft_printf("%s\n", &str + (len - 4));
    if (ft_strncmp(".ber", str + len - 4, 4) == 0)
        return (true);
    return (false);
}

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
	// ?
	if (map.data.elems == 0)
		return (write(2, "Error\nMap invalid\n", 18));
	ft_printf("%d\n", find(&map.data, PLAYER));
	ft_printf("%d\n", count(&map.data, PLAYER));
	ft_printf("%d\n", count(&map.data, COLLECTABLE));
	//mlx_set_setting(MLX_STRETCH_IMAGE, true);
	map.window = init_window(&map.data);
	draw_background(&map.data, map.window);
	draw_foreground(&map.data, map.window);
	mlx_key_hook(map.window, &key_hook, &map);
	mlx_loop(map.window);
	mlx_close_window(map.window);
	return (0);
}
