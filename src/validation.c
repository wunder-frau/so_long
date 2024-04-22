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
