#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

# include "MLX42/include/MLX42/MLX42.h"

# include "libft/libft.h"

# ifndef TILE
#  define TILE 50
# endif
# ifndef TEXTURE_FLOOR
#  define TEXTURE_FLOOR "./textures/wall.png"
# endif
# ifndef TEXTURE_WALL
#  define TEXTURE_WALL "./textures/test_green.png"
# endif
# ifndef TEXTURE_PLAYER
#  define TEXTURE_PLAYER "./textures/player.png"
# endif
# ifndef TEXTURE_EXIT
#  define TEXTURE_EXIT "./textures/exit.png"
# endif
# ifndef TEXTURE_COLLECTABLE
#  define TEXTURE_COLLECTABLE "./textures/collectable.png"
# endif

typedef enum e_symbol
{
	COLLECTABLE,
	ESCAPE,
	OBSTACLE,
	PLAYER,
	SPACE
} t_symbol;

/**
 * data is a flatten array.
 */
typedef struct s_span
{
	t_symbol	*elems;
	int			nx;
	int			ny;
} t_span;

/**
 * Workaround to pass multiple arguments to mlx_key_hook
 */
typedef struct s_map
{
	t_span	data;
	mlx_t	*window;
} t_map;

int open_file(const char *file);

# endif