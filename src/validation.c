#include "../so_long.h"

static bool	is_constrained(const t_span *data, int i)
{
	return (data->elems[i + 1] == OBSTACLE &&
			data->elems[i + 1] == OBSTACLE &&
			data->elems[i + data->nx] == OBSTACLE &&
			data->elems[i - data->nx] == OBSTACLE);
}

/**
 * Must be called after map validation
 * (since i + nx and i - nx can be out of range for man invalid map)
 */
void	check_constrained(const t_span *data)
{
	int	i;

	i = 0;
	while (i < data->nx * data->ny)
	{
		if (data->elems[i] == COLLECTABLE && is_constrained(data, i))
		{
			ft_printf("Error: elem (%d,%d) is constrained", i / data->nx, i % data->nx);
			exit(1);
		}
		i++;
	}
}

void	check_frst_lst_lines(const t_span *data)
{
	int i;

	i = 0;
	while (i < data->nx)
	{
		if (data->elems[i] != OBSTACLE)
		{
			ft_printf("Error: symbol at index %d in first line is not an obstacle\n", i);
			print(data);
			exit(1);
		}
		i++;
	}
	i = (data->nx * data->ny) - data->nx;
	while (i < ((data->nx * data->ny) - data->nx) + data->nx)
	{
		if (data->elems[i] != OBSTACLE)
		{
			ft_printf("Error: symbol at index %d in last line is not an obstacle\n", i);
			print(data);
			exit(1);
		}
		i++;
	}
}

void	check_frst_lst_symb(const t_span *data)
{
	int	y;
	int	first_index;
	int	last_index;

	y = 0;
	while (y < data->ny)
	{
		first_index = y * data->nx;
		last_index = first_index + data->nx - 1;
		if (data->elems[first_index] != OBSTACLE)
		{
			ft_printf("Error: symbol at index %d in the first position of line %d is not an obstacle\n", first_index, y);
			print(data);
			exit(1);
		}
		if (data->elems[last_index] != OBSTACLE)
		{
			ft_printf("Error: symbol at index %d in the last position of line %d is not an obstacle\n", last_index, y);
			print(data);
			exit(1);
		}
		y++;
	}
}

static void	filll(t_span *data, int index, const t_symbol init, const t_symbol to_fill)
{
	if (index < 0 || index > data->nx * data->ny || 
		(data->elems[index] != init && data->elems[index] != to_fill))
		return;
	data->elems[index] = COLLECTABLE;
	filll(data, index - 1, init, to_fill);
	filll(data, index + 1, init, to_fill);
	filll(data, index - data->nx, init, to_fill);
	filll(data, index + data->nx, init, to_fill);
}

t_span	copy_span(const t_span	*in)
{
	int		i;
	t_span	dup;
	dup.nx = in->nx;
	dup.ny = in->ny;
	dup.elems = (t_symbol *) malloc(sizeof(t_symbol) * dup.nx * dup.ny);
	if (!dup.elems)
		return (dup);
	i = 0;
	while(i < dup.nx * dup.ny)
	{
		dup.elems[i] = in->elems[i];
		i++;
	}
	return (dup);
}

void	flood_fill(const t_span *data_ptr, const t_symbol init)
{
	t_span dup;
	// // fill(grid, size, begin, grid[begin.y][begin.x]);
	// ft_printf("data->nx * data->ny %d\n", data->nx * data->ny);
	// ft_printf("pidor %d\n", index);
	dup = copy_span(data_ptr);
	filll(&dup, find(data_ptr, init), init, SPACE);
	print(data_ptr);
	ft_printf("\n\n");
	print(&dup);
}