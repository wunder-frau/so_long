#include "../so_long.h"
#include "string.h"

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
    s.floor = init_image(&s, FLOOR_TEXTURE, '0');
    s.obstacle = init_image(&s, WALL_TEXTURE, '1');

    free(s.flatten);
    return (mlx);
}

void window_input_hook(void *param) {
    if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
        mlx_close_window(param);
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
    mlx_loop(mlx);
    mlx_close_window(mlx);
    return 0;
}
