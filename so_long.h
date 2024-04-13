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

typedef enum e_symbol {
	collectable,
	escape,
	obstacle,
	player,
	space
} t_symbol;

/**
 * data is a flatten array.
 */
typedef struct s_span {
	t_symbol	*data;
	int			nx;
	int			ny;
} t_span;

# endif