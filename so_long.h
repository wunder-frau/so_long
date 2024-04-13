#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

# include "libft/libft.h"

typedef enum e_symbol {
	collectable,
	escape,
	obstacle,
	player,
	space
} t_symbol;

/**
 * Data is a flatten array.
 */
typedef struct s_span {
	t_symbol	*data;
	int			nx;
	int			ny;
} t_span;

# endif