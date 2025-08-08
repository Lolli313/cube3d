NAME = cube3d
CFLAGS = -g -Wall -Wextra -Werror
DEPS = -Iinclude -Imlx_linux -Ilibft
MLXFLAGS = -Lmlx_linux -lmlx -lXext -lX11 -lm
SRCDIR = ./src/
SRC = $(SRCDIR)main.c $(SRCDIR)hooks.c $(SRCDIR)init.c $(SRCDIR)check.c $(SRCDIR)draw.c $(SRCDIR)draw_rays.c \
		$(SRCDIR)update_player.c $(SRCDIR)raycasting.c $(SRCDIR)textures.c
LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a
OBJDIR = obj/
OBJ = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

default: all

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	cc $(CFLAGS) -c $< -o $@ $(DEPS)

$(NAME): $(OBJ)
	make -C $(LIBFTDIR)
	cp $(LIBFT) $(NAME)
	cc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLXFLAGS)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

$(LIBFT):
	make -C $(LIBFTDIR) all

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: all clean fclean re