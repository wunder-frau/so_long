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
void	check_constrained(const t_span *data, const t_symbol elem)
{
	int	i;

	i = 0;
	while (i < data->nx * data->ny)
	{
		if (data->elems[i] == elem && is_constrained(data, i))
		{
			ft_printf("Error: elem=[%d] (%d,%d) is constrained", elem, i / data->nx, i % data->nx);
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

static void	filll(t_span *data, const int index)
{
	// ft_printf("%d[%d]", index > data->nx * data->ny, )
	if (index >= 0 && index < data->nx * data->ny &&
		data->elems[index] != OBSTACLE)
	{
		data->elems[index] = OBSTACLE;
		filll(data, index - 1);
		filll(data, index + 1);
		filll(data, index - data->nx);
		filll(data, index + data->nx);
	}
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
	t_span	dup;
	int		i;

	dup = copy_span(data_ptr);
	print(&dup);
	ft_printf("\n\n");
	filll(&dup, find(data_ptr, init));
	print(&dup);
	ft_printf("\n\n");
	i = 0;
	while (i < dup.nx * dup.ny)
	{
		if (dup.elems[i] != OBSTACLE && dup.elems[i] != SPACE)
		{
			ft_printf("Error: !!!");
			free(dup.elems);
			exit(1);
		}
		i++;
	}
	// print(data_ptr);
	// ft_printf("\n\n");
	// print(&dup);
}