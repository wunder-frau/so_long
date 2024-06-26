/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:57:01 by istasheu          #+#    #+#             */
/*   Updated: 2024/04/26 14:57:03 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	safe_open(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n opening the file\n", 2);
		close(fd);
		exit(1);
	}
	return (fd);
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
