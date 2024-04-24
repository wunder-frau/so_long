#include "flood_fill.h"

// void	fill(t_span *data, const int index, t_symbol to_fill)

void	fill(char **grid, t_point size, t_point cur, char to_fill)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0
	|| cur.x >= size.x || grid[cur.y][cur.x] != to_fill)
		return ;
	grid[cur.y][cur.x] = '8';
	fill(grid, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(grid, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(grid, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(grid, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	flood_fill(char	**grid, t_point size, t_point begin)
{
	// fill(grid, size, begin, grid[begin.y][begin.x]);
	fill(grid, size, begin, '0');
}