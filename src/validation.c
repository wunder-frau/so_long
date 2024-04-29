/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:56:38 by istasheu          #+#    #+#             */
/*   Updated: 2024/04/26 14:56:40 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_frst_lst_lines(const t_span *data)
{
	int	i;

	i = 0;
	while (i < data->nx)
	{
		if (data->elems[i] != OBSTACLE)
		{
			ft_putstr_fd("Error\n Symb in first line is not '1'\n", 2);
			exit(1);
		}
		i++;
	}
	i = (data->nx * data->ny) - data->nx;
	while (i < data->nx * data->ny)
	{
		if (data->elems[i] != OBSTACLE)
		{
			ft_putstr_fd("Error\n Symb in last line is not '1'\n", 2);
			exit(1);
		}
		i++;
	}
}

void	check_frst_lst_symb(const t_span *data)
{
	int	y;
	int	line_begin;
	int	line_end;

	y = 0;
	while (y < data->ny)
	{
		line_begin = y * data->nx;
		line_end = line_begin + data->nx - 1;
		if (data->elems[line_begin] != OBSTACLE)
		{
			ft_putstr_fd("Error\n Symb in first pos is not '1'\n", 2);
			exit(1);
		}
		if (data->elems[line_end] != OBSTACLE)
		{
			ft_putstr_fd("Error\n Symb in last pos is not '1'\n", 2);
			exit(1);
		}
		y++;
	}
}

static t_span	copy_span(const t_span *in)
{
	int		i;
	t_span	dup;

	dup.nx = in->nx;
	dup.ny = in->ny;
	dup.elems = (t_symbol *) malloc(sizeof(t_symbol) * dup.nx * dup.ny);
	if (!dup.elems)
		return (dup);
	i = 0;
	while (i < dup.nx * dup.ny)
	{
		dup.elems[i] = in->elems[i];
		i++;
	}
	return (dup);
}

static void	flood_fill(t_span *data, const int index)
{
	if (index >= 0 && index < data->nx * data->ny
		&& data->elems[index] != OBSTACLE)
	{
		data->elems[index] = OBSTACLE;
		flood_fill(data, index - 1);
		flood_fill(data, index + 1);
		flood_fill(data, index - data->nx);
		flood_fill(data, index + data->nx);
	}
}

void	validate_map(const t_span *data_ptr, const t_symbol init)
{
	t_span	dup;
	int		i;

	dup = copy_span(data_ptr);
	if (!dup.elems)
	{
		ft_putstr_fd("Error\n Memory allocation\n", 2);
		free(dup.elems);
		exit(1);
	}
	flood_fill(&dup, find(data_ptr, init));
	i = 0;
	while (i < dup.nx * dup.ny)
	{
		if (dup.elems[i] != OBSTACLE && dup.elems[i] != SPACE)
		{
			ft_putstr_fd("Error\n Should be obstacles and spaces.\n", 2);
			free(dup.elems);
			exit(1);
		}
		i++;
	}
	free(dup.elems);
}
