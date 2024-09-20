SRC = src/main.c src/path.c src/init.c src/env.c src/tokenizer.c src/signal.c \
		${MINI_SRC}

MINI_SRC = src/mini/cd.c src/mini/echo.c src/mini/env.c src/mini/export.c src/mini/pwd.c src/mini/unset.c src/mini/exit.c

TEST = test.c

TESTO = ${TEST:.c=.o}

HEADERS = -I ./src/ -I ~/.brew/Cellar/readline/8.2.13/include

OBJS = ${SRC:.c=.o}

CC = cc

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

LIBFT = libft/libft.a

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} $(HEADERS) -g3 -c $< -o ${<:.c=.o}

clean:
	@make -C ./libft clean
	rm -f ${OBJS}

fclean: clean
	@make -C ./libft fclean
	rm -f ${NAME}

re: fclean all

${NAME}: ${OBJS}
	@make -C ./libft bonus
	${CC} ${CFLAGS} ${OBJS} -fsanitize=address $(HEADERS) ${LIBFT} -g3 -o ${NAME} -lreadline -L ~/.brew/Cellar/readline/8.2.13/lib

test: ${TESTO}
	@make -C ./libft bonus
	${CC} ${CFLAGS} ${TESTO} ${LIBFT} -g3 -o test -lreadline