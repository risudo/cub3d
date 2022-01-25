NAME = cub3D

CC = gcc

X11 = //usr/X11/include/../lib
MLX_DIR = ./minilibx-linux/

INC = -I$(X11) -I$(MLX_DIR) -I$(INCDIR)

CFLAGS = $(INC) -g -fsanitize=address

LIBS =  -L$(MLX_DIR) -lmlx_Darwin -L$(X11) -lXext -lX11 -lm

INCDIR	=	./include
OBJDIR	=	./objs
DPSDIR	=	./dps

VPATH = src:\
		src/draw:\
		src/init:\
		src/utils:\
		src/cubfile

SRCS =	main.c \
		key_hook.c \
		get_next_line_utils.c \
		get_next_line.c \
		read_cubfile.c


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
