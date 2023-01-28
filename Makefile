
SRC = main.c

OBJ = ${SRC:.c=.o}

NAME = so_long

CC = gcc

LIBD = libft/
LIB = libft.a
MINILIBD = mlx/
MINILIB = libmlx.a

all: ${MINILIBD}${MINILIB} ${LIBD}${LIB} ${NAME}

${MINILIBD}${MINILIB}:
	${MAKE} -C ${MINILIBD}

${LIBD}${LIB}:
	${MAKE} -C ${LIBD}
	${MAKE} -C ${LIBD} bonus

${NAME}: ${OBJ}
		${CC} -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME} ${OBJ} ${LIBD}${LIB} ${MINILIBD}${MINILIB}

clean:
	@rm -f ${OBJ}
	${MAKE} -C ${LIBD} fclean
	${MAKE} -C ${MINILIBD} clean

fclean: clean
	@rm -f ${OBJ} ${NAME}

push: clean
	@git add .
	@git commit -m "makefile push..."
	@git push origin master

run: all
	@./so_long "default.map"
