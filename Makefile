NAME = cub3D

CC = gcc

X11 = //usr/X11/include/../lib
MLX_DIR = ./minilibx-linux/

INC = -I$(X11) -I$(MLX_DIR) -I$(INCDIR)

INCDIR    =    ./include
OBJDIR    =    ./objs
DPSDIR    =    ./dps

CFLAGS = $(INC) -g -fsanitize=address #-Wall -Wextra -Werror

LIBS =  -L$(MLX_DIR) -lmlx_Darwin -L$(X11) -lXext -lX11 -lm


VPATH = ./src:\
		./src/draw:\
		./src/init:\
		./src/utils:\
		./src/cubfile

SRCS = main.c \
	   key_hook.c \
	   get_next_line_utils.c \
	   get_next_line.c \
	   read_cubfile.c


OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DPS = $(addprefix $(DPSDIR)/, $(notdir $(SRCS:.o=.d)))


all: makedir $(NAME)

# $(NAME): $(MLX_DIR) $(OBJ)
# 	$(MAKE) -C $(MLX_DIR)
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

print:
	@echo $(OBJS)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -MF $(DPSDIR)/$(notdir $(<:.c=.d)) -c $(notdir $<) -o $@

-include $(DPS)

makedir :
	@mkdir -p $(OBJDIR)
	@mkdir -p $(DPSDIR)

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJDIR) $(DPSDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

gnl:
	gcc -g -o read_all read_cubfile.c get_next_line.c get_next_line_utils.c

.PHONY: all clean fclean re
