NAME = cube3d
CFLAGS = -g -Wall -Wextra -Werror
DEPS = -Iinclude -Imlx_linux
MLXFLAGS = -Lmlx_linux -lmlx -lXext -lX11 -lm
SRCDIR = ./src/
SRC = $(SRCDIR)main.c $(SRCDIR)hooks.c $(SRCDIR)init.c $(SRCDIR)check.c $(SRCDIR)draw.c $(SRCDIR)draw_rays.c \
		$(SRCDIR)update_player.c $(SRCDIR)raycasting.c
OBJDIR = obj/
OBJ = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

default: all

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	cc $(CFLAGS) -c $< -o $@ $(DEPS)

$(NAME): $(OBJ)
	cc $(CFLAGS) -o $(NAME) $(OBJ) $(MLXFLAGS)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: all clean fclean re