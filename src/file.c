#include "../so_long.h"

int open_file(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening the file\n", 2);
		perror(file);
	}
	return (fd);
}

/**
 * Calculate first line length.
 */
int get_line_len(const char *file)
{
	int		count;
	int		fd;
	char	c;

	fd = open_file(file);
	count = 0;
	while (read(fd, &c, 1) > 0) {
		if (c == '\n')
			break;
		count++;
	}
	close(fd);
	return (count);
}

int count_rows(const char *file)
{
	int		count;
	int		fd;
	char	c;
	int		eof;

	fd = open_file(file);
	count = 0;
	eof = 0;
	while (read(fd, &c, 1) > 0) {
		if (c == '\n')
			count++;
		else if (c == EOF)
			eof = 1;
	}
	close(fd);
	if (!eof)
		count++;
	return count;
}

t_span	init(const char *file)
{
	t_span	data;

	data.nx = get_line_len(file);
	data.ny = count_rows(file);
	if (data.nx == 0 || data.ny == 0) {
        printf("Error: File is empty\n");
        exit(1);
    }
	data.elems = (t_symbol *) malloc(sizeof(t_symbol) * data.nx * data.ny);
	if (!data.elems)
	{
		ft_printf("Error: memory allocation");
		//free(data.elems);
		exit(1);
	}
	fill(file, &data);
	validate_map(&data, PLAYER);
	check_frst_lst_symb(&data);
	check_frst_lst_lines(&data);
	if (count(&data, PLAYER) != 1 || count(&data, ESCAPE) != 1)
	{
		ft_printf("Error: none or multiple players or escapes found on the data");
		free(data.elems);
		exit(1);
	}
	//free(&data);
	return (data);
}
