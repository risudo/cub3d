NAME = cub3D

CC = gcc

X11 = //usr/X11/include/../lib
MLX_DIR = ./minilibx-linux/

INC = -I$(X11) -I$(MLX_DIR) -I$(INCDIR)

CFLAGS = $(INC) -Wall -Wextra -Werror

LIBS =  -L$(MLX_DIR) -lmlx_Darwin -L$(X11) -lXext -lX11 -lm

INCDIR	=	./include
OBJDIR	=	./objs
DPSDIR	=	./dps

VPATH = src:\
		src/draw:\
		src/game:\
		src/utils:\
		src/cubfile

SRCS =	main.c \
		get_next_line_utils.c \
		get_next_line.c \
		read_file.c \
		init_cubfile.c \
		init_player.c \
		validate_map.c \
		get_path_to_texture.c \
		get_color.c \
		skip_empty_line.c \
		init_player_dir.c \
		init_player_pos.c \
		calc_coordinates_of_wall.c \
		calc_wall_height.c \
		dda.c \
		draw_line.c \
		draw_screen.c \
		init_ray.c \
		pixel_color.c \
		set_wall.c \
		key_hook.c \
		init_textures.c \
		init_game.c \
		game_loop.c \
		destroy_and_exit.c \
		ft_split.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_strncmp.c \
		xmalloc.c \
		xput_error.c \
		clear_string_array.c \
		duplicate_map.c \


# init_textures.c 


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

.PHONY: all clean fclean re
