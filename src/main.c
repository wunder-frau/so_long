/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:55:54 by istasheu          #+#    #+#             */
/*   Updated: 2024/04/26 14:55:56 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n To few arguments\n", 2);
		exit(1);
	}
	if (!ends_with_ber(argv[1]))
	{
		ft_putstr_fd("Error\n Invalid file format. Use a .ber file.\n", 2);
		exit(1);
	}
	map.data = init(argv[1]);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	map.window = init_window(&map.data);
	draw_background(&map.data, map.window);
	draw_foreground(&map.data, map.window);
	mlx_key_hook(map.window, &key_hook, &map);
	mlx_loop(map.window);
	mlx_terminate(map.window);
	return (0);
}
