#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "./MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"

// # ifndef TILE_SIZE
// #  define TILE_SIZE 50
// # endif

// # ifndef FLOOR_TEXTURE
// #  define FLOOR_TEXTURE "./textures/space_blue.png"
// # endif
// # ifndef WALL_TEXTURE
// #  define WALL_TEXTURE "./textures/wall.png"
// # endif
// # ifndef PLAYER_TEXTURE
// #  define PLAYER_TEXTURE "./textures/player.png"
// # endif
// # ifndef EXIT_TEXTURE
// #  define EXIT_TEXTURE "./textures/exit.png"
// # endif
// # ifndef COLLECTABLE_TEXTURE
// #  define COLLECTABLE_TEXTURE "./textures/collectable.png"
// # endif
// # ifndef P_TEXTURE
// #  define P_TEXTURE "./textures/player_.png"

typedef struct s_point {
    char c;
    int x, y;
} t_point;

typedef struct s_span {
    t_point *flatten;
    int nx, ny;
} t_span;

# endif