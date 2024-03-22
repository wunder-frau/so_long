#include "../so_long.h"

// int	open_file(char	*file)
// {
// 	int	fd;

// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("Error\n", 2);
// 		perror(file);
// 	}
// 	return (fd);
// }
// t_span	**create_grid(char	*file)
// {
//     while (y < ny) // by line
//     {
//         char *line = get_next_line();
//         while (x < nx)
//         {
//             // var 0
//             t_point p;
//             p.c = line[x];
//             p.x = x;
//             p.y = y;
//             flatten[nx * y + x] = p;

//             // var 1
//             // flatten[nx * y + x] = Point{.c = line[x], .x = x, .y = y};
//             // ++x;
//         }
//         ++y;
//     }
// }

int main () {
    t_span s;
    s.nx = 3;
    s.ny = 3;
    s.flatten = (t_point *)malloc(sizeof(t_point) * s.nx * s.ny);

    s.flatten[0] = (t_point){'a', 0, 0};
    s.flatten[1] = (t_point){'b', 1, 0};
    s.flatten[2] = (t_point){'c', 2, 0};

    s.flatten[3] = (t_point){'d', 0, 1};
    s.flatten[4] = (t_point){'e', 1, 1};
    s.flatten[5] = (t_point){'f', 2, 1};

    s.flatten[6] = (t_point){'0', 0, 2};
    s.flatten[7] = (t_point){'1', 1, 2};
    s.flatten[8] = (t_point){'2', 2, 2};

    {
        int y = 0;
        while (y < s.ny)
        {
            int x = 0;
            while (x < s.nx) {
                printf("%c ", s.flatten[s.nx * y + x].c);
                ++x;
            }
            printf("\n");
            ++y;
        }
    }
    return 0;
}