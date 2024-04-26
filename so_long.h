#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdbool.h>

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# ifndef TILE
#  define TILE 50
# endif
# ifndef TEXTURE_FLOOR
#  define TEXTURE_FLOOR "./textures/wall.png"
# endif
# ifndef TEXTURE_WALL
#  define TEXTURE_WALL "./textures/space.png"
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
}	t_symbol;

typedef enum e_direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
}	t_direction;

/**
 * data is a flatten array.
 */
typedef struct s_span
{
	t_symbol	*elems;
	int			nx;
	int			ny;
}	t_span;

/**
 * Workaround to pass multiple arguments to mlx_key_hook
 */
typedef struct s_map
{
	t_span	data;
	mlx_t	*window;
}	t_map;

// data.c
t_symbol	convert(const char obj);
char		*get_path(const t_symbol s);
void		fill(const char *file, t_span *data);
int			find(const t_span *data, const t_symbol s);

// file.c
int			count(const t_span *data, const t_symbol s);
t_span		init(const char *file);

// move.c
void		move_player(t_map *map, const t_direction d);

// draw.c
mlx_t		*init_window(const t_span *data);
mlx_image_t	*get_image(mlx_t *window, const t_symbol s);
void		draw_background(const t_span *data, mlx_t *window);
void		draw_foreground(const t_span *data, mlx_t *window);
void		key_hook(mlx_key_data_t keydata, void *args);

// validation.c
void		check_frst_lst_lines(const t_span *data);
void		check_frst_lst_symb(const t_span *data);
void		validate_map(const t_span *data, const t_symbol init);

// utils.c
void		handle_moves(void);
bool		ends_with_ber(const char *str);
int			open_file(const char *file);

# endif