NAME		=	so_long
CC			=	cc
CFLAGS	=	-Wextra -Wall -Werror -Wunreachable-code -Ofast -g
SRCS		=	$(addprefix ./src/, data.c file.c move.c \
							draw.c validation.c main.c)
OBJS		=	$(SRCS:.c=.o)
HEADER		=	so_long.h
GLFW_DIR	=	/Users/$(USER)/.brew/opt/glfw/lib
MLX			=	MLX42/build/libmlx42.a
MLX_HEADER	=	MLX42/include/MLX42/MLX42.h
LIBFT		=	libft/libft.a

all:			$(NAME)

$(LIBFT):
					@make -C ./libft

$(MLX):
					@cd MLX42 && cmake -B build && cmake --build build -j4

$(NAME):		$(OBJS) $(MLX) $(LIBFT) $(HEADER)
					@$(CC) $(OBJS) $(MLX) $(LIBFT) -ldl -pthread -lm -L$(GLFW_DIR) -lglfw -I $(MLX_HEADER) -o $(NAME)

%.o:			%.c
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
					@rm -f $(OBJS)
					@rm -rf MLX42/build
					make fclean -C ./libft

fclean:			clean
					@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re