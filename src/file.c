/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:55:38 by istasheu          #+#    #+#             */
/*   Updated: 2024/04/26 14:55:41 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/**
 * Calculate first line length.
 */
static int	get_first_line_len(const char *file)
{
	int		count;
	int		fd;
	char	c;

	fd = open_file(file);
	count = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
		count++;
	}
	close(fd);
	return (count);
}

static int	count_rows(const char *file)
{
	int		count;
	int		fd;
	char	c;

	fd = open_file(file);
	count = 0;
	if (fd == -1)
		return (-1);
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			count++;
	}
	close(fd);
	if (count > 0 && c != '\n')
		count++;
	return (count);
}

static void	validate_span(t_span *data)
{
	validate_map(data, PLAYER);
	check_frst_lst_symb(data);
	check_frst_lst_lines(data);
	if (count(data, PLAYER) != 1 || count(data, ESCAPE) != 1)
	{
		ft_putstr_fd("Error\nInvalid player or escape data\n", 2);
		free(data->elems);
		exit(1);
	}
}

t_span	init(const char *file)
{
	t_span	data;

	data.nx = get_first_line_len(file);
	data.ny = count_rows(file);
	if (data.nx == 0 || data.ny == 0)
	{
		ft_putstr_fd("Error\n: File is empty\n", 2);
		exit(1);
	}
	data.elems = (t_symbol *) malloc(sizeof(t_symbol) * data.nx * data.ny);
	if (!data.elems)
	{
		ft_putstr_fd("Error: memory allocation", 2);
		exit(1);
	}
	fill(file, &data);
	validate_span(&data);
	return (data);
}
