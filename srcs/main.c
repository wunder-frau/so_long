#include "../so_long.h"
#include "string.h"

int	open_file(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		perror(file);
	}
	return (fd);
}

// int first_line_len(char *line)
// {
//     int first_line_len = 0;
//     int i = 0;
//     while (line[i] && line[i] != '\n')
//     {
//         //first_line_len = ft_strlen(line);
//         first_line_len++;
//         i++;
//     }
//     // ft_putstr(line);
//     // ft_printf("/n");
//     printf("\nfirst_line_len: %d\n", first_line_len);
//     return (first_line_len);
// }
int first_line_len(char *file)
{
    int first_line_len = 0;
    int fd = open_file(file);
    if (fd == -1)
    {
        // Error opening file
        return -1;
    }

    char c;
    while (read(fd, &c, 1) > 0)
    {
        if (c == '\n')
        {
            break; // Stop counting at the first newline character
        }
        first_line_len++;
    }

    close(fd);

    //printf("\nfirst_line_len: %d\n", first_line_len);

    return first_line_len;
}

// int count_rows(char *file) {
//     int fd = open_file(file);
//     int row_count = 0;
//     char c;
    
//     while (read(fd, &c, 1) > 0) {
//         if (c == '\n') {
//             row_count++;
//         }
//     }
    
//     close(fd);
//     return row_count;
// }
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

// int first_line_len(char *file)
// {
//     int first_line_len = 0;
//     int fd;
//     char *line;

//     fd = open_file(file);
//     line = get_next_line(fd);
//     close(fd);

//     if (!line)
//     {
//         return -1;
//     }

//     int i = 0;
//     while (line[i] && line[i] != '\n')
//     {
//         first_line_len++;
//         i++;
//     }

//     printf("\nfirst_line_len: %d\n", first_line_len);
//     free(line);

//     return (first_line_len);
// }

void parse_map(char *file, t_span *s)
{
    int     fd;
    int     y;
    int     x;
    t_point p;

    fd = open_file(file);
    y = 0;
    while (y < s->ny) {
        char *line = get_next_line(fd);
        //ft_strlen_gnl(line);
        //s->nx = first_line_len(line);
        x = 0;
        while (x < s->nx)
        {
            p.c = line[x];
            p.x = x;
            p.y = y;
            s->flatten[s->nx * y + x] = p;
            ++x;
        }
        free(line);
        ++y;
    }
    close(fd);
}

t_point *init_map(char *file)
{ 
    t_span s;
    printf("\ninit_map00: %d\n", s.nx);
    s.nx = first_line_len(file);
    //s.nx = 13;
    printf("\ninit_map0: %d\n", s.nx);
    s.ny = count_rows(file);

    s.flatten = (t_point *)malloc(sizeof(t_point) * s.nx * s.ny);
    parse_map(file, &s);

    printf("\ninit_map1: %d\n", s.nx);

    int y = 0;
    while (y < s.ny)
    {
        int x = 0;
        while (x < s.nx)
        {
            printf("%c", s.flatten[s.nx * y + x].c);
            ++x;
        }
        printf("\n");
        ++y;
    }
    return (s.flatten);
}
// mlx_t *init_window(int nx, int ny)
// {
//     mlx_t *mlx;

//     mlx = mlx_init((nx + 1) * 50, (ny + 1) * 50, "so_long", true);
//     if (!mlx)
//         return NULL;

//     return mlx;
// }
// mlx_t *init_window(char *file)
// { 
//     t_span s;
//     s.nx = first_line_len(file);
//     s.ny = count_rows(file);

//     s.flatten = (t_point *)malloc(sizeof(t_point) * s.nx * s.ny);
//     parse_map(file, &s);

//     int window_width = (s.nx + 1) * 50;
//     int window_height = (s.ny + 1) * 50;

//     // Initialize window
//     mlx_t *mlx = mlx_init(window_width, window_height, "Map Window", true);

//     // Free allocated memory for the flattened array
//     free(s.flatten);

//     return mlx;
// }

void	window_input_hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

mlx_t *init_window(char *file) {
    t_span s;
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

    int window_width = (s.nx + 1) * 50;
    int window_height = (s.ny + 1) * 50;

    // Initialize window
    mlx_t *mlx = mlx_init(window_width, window_height, "Map Window", true);
    if (!mlx) {
        fprintf(stderr, "Error: Failed to initialize window\n");
        free(s.flatten); // Free allocated memory before returning
        return NULL;
    }

    free(s.flatten);

    return mlx;
}

int main(int argc, char **argv)
{
    t_point *data;
    mlx_t *mlx;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s map_file\n", argv[0]);
        return 1; // Return error code
    }

    data = init_map(argv[1]);
    if (!data) {
        fprintf(stderr, "Error initializing map\n");
        return 1; // Return error code
    }

    mlx = init_window(argv[1]);
    if (!mlx) {
        fprintf(stderr, "Error initializing window\n");
        free(data);
        return 1; // Return error code
    }

    // Set up key hook
    //mlx_key_hook(mlx, &window_input_hook, data);
    if (mlx_loop_hook(mlx, &window_input_hook, mlx) == 0)
		return (-1);
    // Start the event loop
    mlx_loop(mlx);

    // Cleanup
    mlx_close_window(mlx);
    free(data);

    return 0; // Return success
}


// int main(int argc, char **argv)
// {
//     t_point *data;
    
//     if (argc != 2)
//         return write(2, "Error\n", 6);
//     data = init_map(argv[1]);
//     // s.nx = first_line_len(argv[1]);
//     // s.ny = count_rows(argv[1]);
//     mlx_t *mlx = init_window(argv[1]);
//     if (!mlx) {
//         fprintf(stderr, "Error initializing window\n");
//         return 1; // Return non-zero to indicate an error
//     }
//     mlx_key_hook(data->window, &key_hook, data);
// 	mlx_loop(data->window);
//     mlx_close_window(data->window);
//     free(data);
//     return 0;
// }