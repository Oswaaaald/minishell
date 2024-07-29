SRC = src/main.c src/mini.c src/path.c

TEST = test.c

TESTO = ${TEST:.c=.o}

HEADERS = src/minishell.h

OBJS = ${SRC:.c=.o}

CC = cc

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

LIBFT = libft/libft.a

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -g3 -c $< -o ${<:.c=.o}

clean:
	@make -C ./libft clean
	rm -f ${OBJS}

fclean: clean
	@make -C ./libft fclean
	rm -f ${NAME}

re: fclean all

${NAME}: ${OBJS}
	@make -C ./libft bonus
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -g3 -o ${NAME} -lreadline

test: ${TESTO}
	@make -C ./libft bonus
	${CC} ${CFLAGS} ${TESTO} ${LIBFT} -g3 -o test -lreadline