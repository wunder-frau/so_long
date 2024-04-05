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
    int fd;
    char *line;

    fd = open_file(file);
    line = get_next_line(fd);
    close(fd);

    if (!line)
    {
        return -1;
    }

    int i = 0;
    while (line[i] && line[i] != '\n')
    {
        first_line_len++;
        i++;
    }

    printf("\nfirst_line_len: %d\n", first_line_len);
    free(line);

    return (first_line_len);
}

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
        ft_strlen_gnl(line);
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
    //s.nx = first_line_len(file);
    s.nx = first_line_len(file);
    printf("\ninit_map0: %d\n", s.nx);
    s.ny = 5;

    s.flatten = (t_point *)malloc(sizeof(t_point) * s.nx * s.ny);
    parse_map(file, &s);

        printf("\ninit_map1: %d\n", s.nx);

    int y = 0;
    while (y < s.ny) {
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

int main(int argc, char **argv)
{
    t_point *data;

    if (argc != 2)
        return write(2, "Error\n", 6);
    data = init_map(argv[1]); 
    free(data);
    return 0;
}