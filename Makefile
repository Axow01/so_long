
SRC = src/main.c src/map_functions.c src/basic_function.c \
	src/flood_fill_colision.c src/errors.c

OBJ = $(patsubst src/%.c,bin/%.o,$(SRC))

NAME = so_long

CC = gcc

LIBD = includes/libft/
LIB = libft.a

MLX = libmlx.a
MLXPATH = includes/mlx/


all: ${LIBD}${LIB} ${NAME}

${LIBD}${LIB}:
	${MAKE} -C ${LIBD}
	${MAKE} -C ${LIBD} bonus

${NAME}: ${OBJ} ${MLXPATH}${MLX}
		${CC} ${MLXPATH}${MLX} ${OBJ} ${LIBD}${LIB} -framework OpenGL -framework AppKit -Imlx -o ${NAME}

${MLXPATH}${MLX}:
		${MAKE} -C ${MLXPATH}
bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f ${OBJ}
	${MAKE} -C ${LIBD} fclean

fclean: clean
	${MAKE} -C ${MLXPATH} clean
	@rm -f ${OBJ} ${NAME}

re: fclean all
