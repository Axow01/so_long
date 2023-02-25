
SRC = main.c map_functions.c basic_function.c flood_fill_colision.c errors.c

OBJ = ${SRC:.c=.o}

NAME = so_long

CC = gcc

LIBD = libft/
LIB = libft.a

MLX = libmlx.a
MLXPATH = mlx/


all: ${LIBD}${LIB} ${NAME}

${LIBD}${LIB}:
	${MAKE} -C ${LIBD}
	${MAKE} -C ${LIBD} bonus
	@echo "uwu......."

${NAME}: ${OBJ} ${MLXPATH}${MLX}
		${CC} -framework OpenGL -framework AppKit -o ${NAME} mlx/libmlx.a ${OBJ} ${LIBD}${LIB}

${MLXPATH}${MLX}:
		${MAKE} -C ${MLXPATH}

clean:
	@rm -f ${OBJ}
	${MAKE} -C ${LIBD} fclean

fclean: clean
	${MAKE} -C ${MLXPATH} clean
	@rm -f ${OBJ} ${NAME}

push: clean
	@git add .
	@git commit -m "makefile push..."
	@git push origin master

run: all
	@./so_long map/default.ber

re: fclean all
