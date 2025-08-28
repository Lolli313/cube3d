NAME = cube3d
CFLAGS = -g -Wall -Wextra -Werror

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLXDIR = mlx_linux
	MLXFLAGS = -L$(MLXDIR) -lmlx -lXext -lX11 -lm
endif
ifeq ($(UNAME_S),Darwin)
	MLXDIR = mlx_macos
	MLXFLAGS = -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit
endif

DEPS = -Iinclude -I$(MLXDIR) -Ilibft
SRCDIR = ./src/
SRC = $(SRCDIR)main.c $(SRCDIR)hooks.c $(SRCDIR)init.c $(SRCDIR)check.c $(SRCDIR)draw.c $(SRCDIR)draw_rays.c \
		$(SRCDIR)update_player.c $(SRCDIR)raycasting.c $(SRCDIR)textures.c $(SRCDIR)check_maps.c \
		$(SRCDIR)parsing.c $(SRCDIR)parsing2.c $(SRCDIR)parsing3.c $(SRCDIR)parsing4.c \
		$(SRCDIR)parsing5.c $(SRCDIR)parsing6.c $(SRCDIR)parsing_main.c $(SRCDIR)draw_wall.c \
		$(SRCDIR)check_wall_side.c $(SRCDIR)cleanup.c $(SRCDIR)flood_fill.c $(SRCDIR)flood_fill1.c \
		$(SRCDIR)flood_fill2.c $(SRCDIR)door.c $(SRCDIR)handle_door.c $(SRCDIR)minimap.c
LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a
OBJDIR = obj/
OBJ = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

default: all

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $< -o $@ $(DEPS)

$(NAME): $(OBJ)
	make -C $(LIBFTDIR)
	make -C $(MLXDIR)
	cp $(LIBFT) $(NAME)
	cc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLXFLAGS)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)
	make -C $(LIBFTDIR) clean
	make -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean
	make -C $(MLXDIR) clean

re: fclean all

$(LIBFT):
	make -C $(LIBFTDIR) all

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: all clean fclean re