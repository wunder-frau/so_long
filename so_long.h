#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
//# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
//# include "MLX42.h"
// # include "libft/ft_printf/ft_printf.h"
// # include "libft/get_next_line/get_next_line.h"

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

typedef struct s_point {
    char            c;
    int             x, y;
} t_point;

typedef struct s_player_pos
{
	int	x;
	int	y;
}	t_player_pos;

typedef struct s_span {
    t_point *flatten;
    int nx, ny;
    mlx_t			*window;
    mlx_image_t		*obstacle;
    mlx_image_t     *floor;
    mlx_image_t     *player;
    mlx_image_t     *collect;
    mlx_image_t     *exit;
    t_point			*map;
	t_player_pos	*player_pos;
} t_span;

# endif