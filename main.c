#include "so_long.h"
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

void first_line_len(char *line)
{
    int first_line_len = 0;
    int i = 0;
    while (line[i] && line[i] != '\n')
    {
        //first_line_len = ft_strlen(line);
        first_line_len++;
        i++;
    }
    // ft_putstr(line);
    // ft_printf("/n");
    printf("\nLength of first line: %d\n", first_line_len);
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
        first_line_len(line);
        x = 0;
        while (x < s->nx) {
            p.c = line[x];
            p.x = x;
            p.y = y;
            s->flatten[s->nx * y + x] = p;
            ++x;
        }
        ++y;
    }
    close(fd);
}

t_point *init_map(char *file)
{ 
    t_span s;
    s.nx = 13;
    s.ny = 5;

    s.flatten = (t_point *)malloc(sizeof(t_point) * s.nx * s.ny);
    parse_map(file, &s);

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