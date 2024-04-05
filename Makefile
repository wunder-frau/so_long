NAME		=	so_long
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
SRCS		=	main.c
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
					@cd MLX42 && cmake -B build && cmake --build build

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

# NAME	:= so_long
# CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
# LIBMLX	:= ./MLX42

# HEADERS	:= -I ./include -I $(LIBMLX)/include
# LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm
# SRCS	:= $(addprefix ./srcs/, error_handler.c main.c map_init.c)
# LIBFT 	:= libft/libft.a
# OBJS	:= ${SRCS:.c=.o}

# all: libmlx $(NAME)

# libmlx:
# 	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# %.o: %.c
# 	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

# $(NAME): $(OBJS)
# 	make -C ./libft
# 	@$(CC) $(OBJS) $(LIBS) $(HEADERS) ./libft/libft.a -o $(NAME)

# clean:
# 	make clean -C ./libft
# 	@rm -rf $(OBJS)
# 	@rm -rf $(LIBMLX)/build

# fclean: clean
# 	make fclean -C ./libft
# 	@rm -rf $(NAME)

# re: fclean all

# .PHONY: all, clean, fclean, re, libmlx