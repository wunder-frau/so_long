NAME	:= so_long
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm
SRCS	:= $(addprefix ./srcs/, window_test.c main.c game.c map.c map_check.c helpers.c)
LIBFT 	:= libft/libft.a
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	make -C ./libft
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) ./libft/libft.a -o $(NAME)

clean:
	make clean -C ./libft
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	make fclean -C ./libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libmlx
