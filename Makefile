
SRC = main.c

OBJ = ${SRC:.c=.o}

NAME = so_long

CC = gcc

LIBD = libft/

LIB = libft.a

all: ${LIBD}${LIB} ${NAME}

${LIBD}${LIB}:
	${MAKE} -C ${LIBD}
	${MAKE} -C ${LIBD} bonus

${NAME}: ${OBJ}
		${CC} -o ${NAME} ${OBJ} ${LIBD}${LIB}

clean:
	@rm -f ${OBJ}
	${MAKE} -C ${LIBD} fclean

fclean: clean
	@rm -f ${OBJ} ${NAME}

push: clean
	@git add .
	@git commit -m "makefile push..."
	@git push origin master
