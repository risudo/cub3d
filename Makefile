NAME = cub3D

CC = gcc

X11 = //usr/X11/include/../lib
MLX_DIR = ./minilibx-linux/

INC = -I$(X11) -I$(MLX_DIR)

CFLAGS = $(INC) -g -fsanitize=address #-Wall -Wextra -Werror

LIBS =  -L$(MLX_DIR) -lmlx_Darwin -L$(X11) -lXext -lX11 -lm

SRC = main.c key_hook.c read_cubfile.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MLX_DIR) $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

gnl:
	gcc -g -o read_all read_cubfile.c get_next_line.c get_next_line_utils.c

.PHONY: all clean fclean re
