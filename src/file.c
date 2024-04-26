#include "../so_long.h"

/**
 * Calculate first line length.
 */
static int	get_line_len(const char *file)
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

int	count(const t_span *data, const t_symbol s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < data->nx * data->ny)
	{
		if (data->elems[i] == s)
			count++;
		++i;
	}
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

	data.nx = get_line_len(file);
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
