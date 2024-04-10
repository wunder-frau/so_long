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
        // Error opening file
        return -1;
    }

    char c;
    while (read(fd, &c, 1) > 0) {
        if (c == '\n') {
            break; // Stop counting at the first newline character
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
    int eof = 0; // Flag to track end of file
    
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

// Separated init_window function
mlx_t *init_window(int nx, int ny) {
    int window_width = (nx + 1) * TILE;
    int window_height = (ny + 1) * TILE;

    // Initialize window
    mlx_t *mlx = mlx_init(window_width, window_height, "Map Window", true);
    if (!mlx) {
        fprintf(stderr, "Error: Failed to initialize window\n");
        return NULL;
    }

    return mlx;
}

mlx_image_t *init_obst(t_span *data) {
    mlx_image_t *obstacle;
    int nx = data->nx;
    int ny = data->ny;
    t_point *flatten = data->flatten;

    // Load the texture
    mlx_texture_t *texture = mlx_load_png("./textures/exit.png");
    if (!texture) {
        fprintf(stderr, "Error: Failed to load texture\n");
        return NULL;
    }

    // Create image from texture
    obstacle = mlx_texture_to_image(data->window, texture);
    mlx_delete_texture(texture);
    if (!obstacle) {
        fprintf(stderr, "Error: Failed to create image from texture\n");
        return NULL;
    }

    // Draw obstacles
    int y = 0;
    while (y < ny) {
        int x = 0;
        while (x < nx) {
            if (flatten[y * nx + x].c == '1') {
                mlx_image_to_window(data->window, obstacle, x * TILE, y * TILE);
            }
            ++x;
        }
        ++y;
    }

    return obstacle;
}

// Modified init_map function to initialize the window as well
mlx_t *init_map(char *file) {
    t_span s;
    mlx_t *mlx;

    s.nx = first_line_len(file);
    if (s.nx == -1) {
        fprintf(stderr, "Error: Failed to determine the size of the first line\n");
        return NULL;
    }
    s.ny = count_rows(file);
    if (s.ny == -1) {
        fprintf(stderr, "Error: Failed to count the number of rows\n");
        return NULL;
    }

    s.flatten = (t_point *)malloc(sizeof(t_point) * s.nx * s.ny);
    if (!s.flatten) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    parse_map(file, &s);

    // Initialize window internally
    mlx = init_window(s.nx, s.ny);
    if (!mlx) {
        fprintf(stderr, "Error initializing window\n");
        free(s.flatten);
        return NULL;
    }

    // Assign the initialized window to the span struct
    s.window = mlx;
    s.obstacle = init_obst(&s);
    free(s.flatten);

    // Return the initialized window
    return mlx;
}

void window_input_hook(void *param) {
    if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
        mlx_close_window(param);
}

int main(int argc, char **argv) {
    mlx_t *mlx;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s map_file\n", argv[0]);
        return 1; // Return error code
    }

    mlx = init_map(argv[1]);
    if (!mlx) {
        fprintf(stderr, "Error initializing window\n");
        return 1; // Return error code
    }

    // Set up key hook
    if (mlx_loop_hook(mlx, &window_input_hook, mlx) == 0)
        ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
    
    // Start the event loop
    mlx_loop(mlx);

    // Cleanup
    mlx_close_window(mlx);

    return 0; // Return success
}
