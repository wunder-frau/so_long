#include "../so_long.h"

int open_file(char *file) {
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1) {
        ft_putstr_fd("Error\n", 2);
        perror(file);
    }
    return (fd);
}
int first_line_len(char *file) {
    int first_line_len = 0;
    int fd = open_file(file);
    if (fd == -1) {
        return -1;
    }
    char c;
    while (read(fd, &c, 1) > 0) {
        if (c == '\n') {
            break;
        }
        first_line_len++;
    }
    close(fd);
    return first_line_len;
}

int count_rows(char *file) {
    int fd = open_file(file);
    int row_count = 0;
    char c;
    int eof = 0;
    
    while (read(fd, &c, 1) > 0) {
        if (c == '\n') {
            row_count++;
        } else if (c == EOF) {
            // If the last character is EOF and not '\n', it's still a line
            // So, we increment row_count
            eof = 1;
        }
    } 
    close(fd);
    // If the file doesn't end with a newline, increment row_count
    if (!eof) {
        row_count++;
    }
    return row_count;
}

void parse_map(char *file, t_span *s) {
    int fd;
    int y;
    int x;
    t_point p;

    fd = open_file(file);
    y = 0;
    while (y < s->ny) {
        char *line = get_next_line(fd);
        x = 0;
        while (x < s->nx) {
            p.c = line[x];
            p.x = x;
            p.y = y;
            s->flatten[s->nx * y + x] = p;
            printf("%c", s->flatten[s->nx * y + x].c);
            ++x;
        }
        printf("\n");
        free(line);
        ++y;
    }
    close(fd);
}

mlx_t *init_window(int nx, int ny) {
    int window_width = (nx) * TILE;
    int window_height = (ny) * TILE;

    mlx_t *mlx = mlx_init(window_width, window_height, "Map Window", true);
    if (!mlx) {
        fprintf(stderr, "Error: Failed to initialize window\n");
        return NULL;
    }

    return mlx;
}

mlx_image_t *init_image(t_span *data, char *texture_path, char target_char) {
    mlx_image_t *image;
    int nx = data->nx;
    int ny = data->ny;
    t_point *flatten = data->flatten;

    mlx_texture_t *texture = mlx_load_png(texture_path);
    image = mlx_texture_to_image(data->window, texture);
    mlx_delete_texture(texture);
    if (!image) {
        fprintf(stderr, "Error: Failed to create image from texture\n");
        return NULL;
    }
    int y = 0;
    while (y < ny) {
        int x = 0;
        while (x < nx) {
            if (flatten[y * nx + x].c == target_char) {
                mlx_image_to_window(data->window, image, x * TILE, y * TILE);
            }
            ++x;
        }
        ++y;
    }
    return image;
}

int init_map_data(char *file, t_span *s) {
    s->nx = first_line_len(file);
    if (s->nx == -1) {
        fprintf(stderr, "Error: Failed to determine the size of the first line\n");
        return -1;
    }
    s->ny = count_rows(file);
    if (s->ny == -1) {
        fprintf(stderr, "Error: Failed to count the number of rows\n");
        return -1;
    }
    s->flatten = (t_point *)malloc(sizeof(t_point) * s->nx * s->ny);
    if (!s->flatten) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return -1;
    }
    parse_map(file, s);
    return 0;
}

int init_player_pos(t_span *data) {
    t_point *flatten = data->flatten;
    int nx = data->nx;
    int ny = data->ny;
    int player_found = 0; 

    data->player_pos = (t_player_pos *)malloc(sizeof(t_player_pos));
    if (!data->player_pos) {
        fprintf(stderr, "Error: Memory allocation failed for player position\n");
        return -1; 
    }

    int y = 0;
    while (y < ny) {
        int x = 0;
        while (x < nx) {
            if (flatten[y * nx + x].c == 'P') {
                data->player_pos->x = x; 
                data->player_pos->y = y; 
                player_found = 1; 
                break; 
            }
            ++x;
        }
        if (player_found) {
        ft_printf("init_player_pos:%d, %d, player_f:%d\n", data->player_pos->x, data->player_pos->y, player_found);
            break;
        }
        ++y;
    }

    if (!player_found) { 
        fprintf(stderr, "Error: Player position not found\n");
        free(data->player_pos); 
        return -1;
    }

    return 0;
}

// int find_player_position_index(t_span *data) {
//     t_point *flatten = data->flatten;
//     int nx = data->nx;
//     int ny = data->ny;

//     int index = -1; 

//     for (int i = 0; i < nx * ny; i++) {
//         if (flatten[i].c == 'P') {
//             index = i; 
//             break; 
//         }
//     }

//     return index;
// }

mlx_t *init_map(char *file) {
    t_span s;
    mlx_t *mlx;

    if (init_map_data(file, &s) == -1) {
        return NULL;
    }
    mlx = init_window(s.nx, s.ny);
    if (!mlx) {
        fprintf(stderr, "Error initializing window\n");
        free(s.flatten);
        return NULL;
    }
    s.window = mlx;
    ft_printf("After initializing player position: x=%d, y=%d\n", s.player_pos->x, s.player_pos->y);
    s.floor = init_image(&s, TEXTURE_FLOOR, '0');
    s.obstacle = init_image(&s, TEXTURE_WALL, '1');
    s.player = init_image(&s, TEXTURE_PLAYER, 'P');
    if (init_player_pos(&s) == -1) {
        fprintf(stderr, "Error initializing player position\n");
        free(s.flatten);
        return NULL;
    }
    s.collect = init_image(&s, TEXTURE_COLLECTABLE, 'C');
    s.exit = init_image(&s, TEXTURE_EXIT, 'E');

    free(s.flatten);
    return mlx;
}

void window_input_hook(void *param) {
    if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
        mlx_close_window(param);
}

bool is_obstacle(t_span *data, int x, int y) {
    int index = y * data->nx + x;

    if (data->flatten[index].c == '1') {
        return false;
    }

    return true;
}

void process_y_move(t_span data, char key) {
    t_player_pos *pos = data.player_pos;

    //ft_printf("Initial Position: x=%d, y=%d\n", data->player_pos->x, data->player_pos->y);
     ft_printf("player position in process_y_move: x=%d, y=%d\n", data.player_pos->x, data.player_pos->y);
    if (key == 'W') {
        if (!is_obstacle(&data, pos->x, pos->y - 1)) {
            pos->y--;
        }
    } else if (key == 'S') {
        if (!is_obstacle(&data, pos->x, pos->y + 1)) {
            pos->y++;
        }
    }

    ft_printf("Final Position: x=%d, y=%d\n", pos->x, pos->y);
}




// void process_y_move(t_span *data, char key) {

//     t_player_pos *pos = data->player_pos;
//     //ft_printf("%d", data->player_pos);

//     if (key == 'W') {
//         // if (!is_obstacle(data, pos->x, (pos->y) - 1))
// 		// {
//             ft_printf("before:%d", pos->y);
//             pos->y--;
//             ft_printf("after:%d", pos->y);
 //mlx_image_to_window(data->window, data->player, pos->x * TILE, pos->y * TILE);
//         //}
//     } else if (key == 'S') {
//             pos->y++;
//     }
// }

// void key_hook(mlx_key_data_t keydata, void *param) {
//     t_span *data = param;

//     // Process key press events
//     if (keydata.action == MLX_PRESS) {
//         if (keydata.key == MLX_KEY_W) {
//             process_y_move(data, 'W');
//         } else if (keydata.key == MLX_KEY_S) {
//             process_y_move(data, 'S');
//         }
//     }
// }



// void	process_y_move(t_span *data, char key)
// {
// 	t_player_pos	*pos;

// 	pos = data->player_pos;

//    // ft_printf("%d", data->player_pos);
// 	if (key == 'W')
// 	{
//         ft_printf("W: %d", data->player_pos);
//         data->player->instances[0].y -= TILE;
// 			data->player_pos->y --;
// 	}
// 	else if (key == 'S')
// 	{
//             ft_printf("S: %d", data->player_pos);
// 			data->player->instances[0].y += TILE;
// 			data->player_pos->y ++;
// 	}
// }

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_span			*data;

	data = param;

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		process_y_move(*data, 'W');
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		process_y_move(*data, 'S');
}
int main(int argc, char **argv) {
    mlx_t *mlx;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s map_file\n", argv[0]);
        return 1;
    }
    mlx = init_map(argv[1]);
    if (!mlx) {
        fprintf(stderr, "Error initializing window\n");
        return 1;
    }
    if (mlx_loop_hook(mlx, &window_input_hook, mlx) == 0)
        ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
    mlx_key_hook(mlx, &key_hook, mlx);
    mlx_loop(mlx);
    mlx_close_window(mlx);
    return 0;
}
