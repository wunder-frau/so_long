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
