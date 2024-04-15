#include "../so_long.h"

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

int	get_delta(const t_span *data, const t_direction d)
{
	switch (d)
	{
	case LEFT:
		return (-1);
	case RIGHT:
		return (+1);
	case UP:
		return (-data->nx);
	case DOWN:
		return (+data->nx);
	}
}

void	redraw_player(mlx_t *window, const int xt, const int yt)
{
	mlx_image_to_window(window, get_image(window, SPACE), xt, yt);
	mlx_image_to_window(window, get_image(window, PLAYER), xt, yt);
}

void	draw_movement(t_map *map, const t_direction d, const int curr)
{
	int			xt;
	int			yt;

	xt = TILE * (curr % map->data.nx);
	yt = TILE * (curr / map->data.nx);
	mlx_image_to_window(map->window, get_image(map->window, SPACE), xt, yt);
	switch (d)
	{
	case LEFT:
		redraw_player(map->window, xt - TILE, yt);
		return ;
	case RIGHT:
		redraw_player(map->window, xt + TILE, yt);
		return ;
	case UP:
		redraw_player(map->window, xt, yt - TILE);
		return ;
	case DOWN:
		redraw_player(map->window, xt, yt + TILE);
		return ;
	}
}

void	move_player(t_map *map, const t_direction d)
{
	int	curr;
	int	delta;

	curr = find(&map->data, PLAYER);
	delta = get_delta(&map->data, d);
	if (!is_possible_move(&map->data, curr + delta))
		return ;
	if (count(&map->data, COLLECTABLE) == 0 && map->data.elems[curr + delta] == ESCAPE)
		mlx_close_window(map->window);
	map->data.elems[curr] = SPACE;
	map->data.elems[curr + delta] = PLAYER;
	draw_movement(map, d, curr);
	// delete
	print(&map->data);
	ft_printf("\n");
}