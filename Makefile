#--- DEFAULT VALUES ---#

NAME = so_long

SRC = src/main.c src/map_functions.c src/basic_function.c \
	src/flood_fill_colision.c src/errors.c src/utils.c

OBJS = $(patsubst src/%.c, bin/%.o, $(SRC))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFTPATH = includes/libft/

LIBFT = libft.a

MLX = libmlx.a

MLXPATH = includes/mlx/

#---   RULES   ---#

all: $(NAME) logo

$(NAME): $(OBJS) $(LIBFTPATH)$(LIBFT) $(MLXPATH)$(MLX)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTPATH) -lft $(MLXPATH)$(MLX) -framework OpenGL -framework AppKit -Imlx -o $(NAME)

bin/%.o: src/%.c
	@mkdir -p bin/
	@$(CC) $(CFLAGS) -c -o $@ $<

$(MLXPATH)$(MLX):
	@$(MAKE) -C $(MLXPATH)

$(LIBFTPATH)$(LIBFT):
	@$(MAKE) -C $(LIBFTPATH)
	@$(MAKE) -C $(LIBFTPATH) bonus

clean:
	@rm -rf bin/
	@$(MAKE) -C $(LIBFTPATH) clean

fclean: clean
	@rm $(NAME)
	@$(MAKE) -C $(MLXPATH) clean
	@$(MAKE) -C $(LIBFTPATH) fclean

bonus: all

re: fclean all

logo:
	@echo "\033[32;1m--- BUILD COMPLETE ---"
	@echo "███▄ ▄███▓ ███▄ ▄███▓ ▄▄▄       ██▀███   ▄████▄   ▒█████  ▄▄▄█████▓▄▄▄█████▓"
	@echo "▓██▒▀█▀ ██▒▓██▒▀█▀ ██▒▒████▄    ▓██ ▒ ██▒▒██▀ ▀█  ▒██▒  ██▒▓  ██▒ ▓▒▓  ██▒ ▓▒"
	@echo "▓██    ▓██░▓██    ▓██░▒██  ▀█▄  ▓██ ░▄█ ▒▒▓█    ▄ ▒██░  ██▒▒ ▓██░ ▒░▒ ▓██░ ▒░"
	@echo "▒██    ▒██ ▒██    ▒██ ░██▄▄▄▄██ ▒██▀▀█▄  ▒▓▓▄ ▄██▒▒██   ██░░ ▓██▓ ░ ░ ▓██▓ ░ "
	@echo "▒██▒   ░██▒▒██▒   ░██▒ ▓█   ▓██▒░██▓ ▒██▒▒ ▓███▀ ░░ ████▓▒░  ▒██▒ ░   ▒██▒ ░ "
	@echo "░ ▒░   ░  ░░ ▒░   ░  ░ ▒▒   ▓▒█░░ ▒▓ ░▒▓░░ ░▒ ▒  ░░ ▒░▒░▒░   ▒ ░░     ▒ ░░   "
	@echo "░  ░      ░░  ░      ░  ▒   ▒▒ ░  ░▒ ░ ▒░  ░  ▒     ░ ▒ ▒░     ░        ░    "
	@echo "░      ░   ░      ░     ░   ▒     ░░   ░ ░        ░ ░ ░ ▒    ░        ░      "
	@echo "       ░          ░         ░  ░   ░     ░ ░          ░ ░                    "
	@echo "                                         ░                                   \033[0m"

