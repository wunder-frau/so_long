#ifndef FLOOD_FILL_H
# define FLOOD_FILL_H

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

void	fill(char **grid, t_point size, t_point cur, char to_fill);
void	flood_fill(char	**grid, t_point size, t_point begin);

#endif
