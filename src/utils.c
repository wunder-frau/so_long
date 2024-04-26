#include "../so_long.h"

void	handle_moves(void)
{
	static int	moves;

	moves++;
	ft_printf("Number of moves: %i\n", moves);
}

bool	ends_with_ber(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (ft_strncmp(".ber", str + len - 4, 4) == 0)
		return (true);
	return (false);
}

int	open_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening the file\n", 2);
		perror(file);
	}
	return (fd);
}
