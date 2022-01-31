NAME = cub3D

CC = gcc

X11 = //usr/X11/include/../lib
MLX_DIR = ./minilibx-linux/

INC = -I$(X11) -I$(MLX_DIR) -I$(INCDIR)

CFLAGS = $(INC) -Wall -Wextra -Werror

ifeq ($(shell uname), Darwin)
	MLX = mlx_Darwin
else
	MLX = mlx
endif

LIBS =  -L$(MLX_DIR) -l$(MLX) -L$(X11) -lXext -lX11 -lm

INCDIR	=	./include
OBJDIR	=	./objs
DPSDIR	=	./dps

VPATH = src:\
		src/draw:\
		src/game:\
		src/utils:\
		src/cubfile

UTILS	=	duplicate_map.c \
			get_next_line_utils.c \
			ft_strlen.c \
			get_next_line.c \
			xput_error.c \
			clear_string_array.c \
			ft_split.c \
			ft_strncmp.c \
			xmalloc.c \
			ft_strdup.c

GAME	=	game_loop.c \
			init_game.c \
			destroy_and_exit.c \
			key_hook.c \
			init_textures.c

CUBFILE	=	init_cubfile.c \
			read_file.c \
			get_color.c \
			skip_empty_line.c \
			get_path_to_texture.c \
			init_player.c \
			init_player_pos.c \
			validate_map.c \
			init_player_dir.c \
			clear_path_to_texture.c

DRAW	=	dda.c \
			calc_coordinates_of_wall.c \
			pixel_color.c \
			draw_line.c \
			set_wall.c \
			calc_wall_height.c \
			init_ray.c \
			draw_screen.c


SRCS	=	$(UTILS) \
			$(GAME) \
			$(CUBFILE) \
			$(DRAW) \
			main.c


OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DPS = $(addprefix $(DPSDIR)/, $(notdir $(SRCS:.o=.d)))

all: makedir $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -MF $(DPSDIR)/$(notdir $(<:.c=.d)) -c $< -o $@

-include $(DPS)

makedir :
	mkdir -p $(OBJDIR)
	mkdir -p $(DPSDIR)

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJDIR) $(DPSDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	norminette ./src ./include

.PHONY: all clean fclean re
