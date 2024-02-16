// // -----------------------------------------------------------------------------
// // Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// // See README in the root project for more information.
// // -----------------------------------------------------------------------------

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <MLX42/MLX42.h>

// #define WIDTH 512
// #define HEIGHT 512

// static mlx_image_t* image;

// // -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			// uint32_t color = ft_pixel(
// 			// 	rand() % 0xFF, // R
// 			// 	rand() % 0xFF, // G
// 			// 	rand() % 0xFF, // B
// 			// 	rand() % 0xFF  // A
// 			// );
// 			//mlx_put_pixel(image, i, y, color);
// 			mlx_put_pixel(image, i, y, 0xD461D3);
// 		}
// 	}
// }


// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

// // -----------------------------------------------------------------------------

// int32_t main(void)
// {
// 	mlx_t* mlx;

// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
	
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }


// Written by Bruh

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* img;
static mlx_image_t* test;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
    (void)param;
    uint32_t i = 0;
    while (i < img->width)
    {
        uint32_t y = 0;
        while (y < img->height)
        {
            uint32_t color = ft_pixel(
                rand() % 0xFF, // R
                rand() % 0xFF, // G
                rand() % 0xFF, // B
                rand() % 0xFF  // A
            );
            mlx_put_pixel(img, i, y, color);
            mlx_put_pixel(test, i, y, 0xD461D3);
            y++;
        }
        i++;
    }
}

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
	// if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
	// 	mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		img->instances[0].x += 5;

	if (mlx_is_key_down(param, MLX_KEY_UP))
		test->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		test->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		test->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		test->instances[0].x += 5;
}


int32_t	main(void)
{

	// MLX allows you to define its core behaviour before startup.
	//mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	img = mlx_new_image(mlx, 56, 56);
	if (!img || (mlx_image_to_window(mlx, img, 180, 50) < 0))
		ft_error();

    test = mlx_new_image(mlx, 100, 100);
	if (!test || (mlx_image_to_window(mlx, test, 50, 50) < 0))
	ft_error();
	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 200, 200, 0xFF0000FF);
	mlx_put_pixel(img, 400, 200, 0xD461D3);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
		mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}