/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:55:12 by istasheu          #+#    #+#             */
/*   Updated: 2024/04/26 14:55:14 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

mlx_t	*init_window(const t_span *data)
{
	mlx_t	*window;

	window = mlx_init(TILE * data->nx, TILE * data->ny, "SO_LONG", true);
	if (!window)
	{
		ft_putstr_fd("Error\n Failed to initialise window\n", 2);
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
		ft_putstr_fd("Error\n Failed to create texture\n", 2);
		mlx_delete_texture(texture);
		exit(1);
	}
	return (image);
}

void	draw_background(const t_span *data, mlx_t *window)
{
	int			i;
	int			xt;
	int			yt;
	t_symbol	curr;

	i = 0;
	while (i < data->nx * data->ny)
	{
		curr = data->elems[i];
		if (curr == COLLECTABLE || curr == PLAYER || curr == ESCAPE)
			curr = SPACE;
		xt = TILE * (i % data->nx);
		yt = TILE * (i / data->nx);
		mlx_image_to_window(window, get_image(window, curr), xt, yt);
		++i;
	}
}

void	draw_foreground(const t_span *data, mlx_t *window)
{
	int			i;
	int			xt;
	int			yt;
	t_symbol	curr;

	i = 0;
	while (i < data->nx * data->ny)
	{
		curr = data->elems[i];
		if (curr == COLLECTABLE || curr == PLAYER || ESCAPE)
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
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(map, LEFT);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(map, RIGHT);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(map, DOWN);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_player(map, UP);
}
