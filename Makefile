SRC = src/main.c src/init.c src/env.c src/signal.c src/free.c src/utils.c \
		${MINI_SRC} \
		${PATH_SRC} \
		${TOKEN_SRC} \
		${EXEC_SRC} \
		${FILER_SRC}

MINI_SRC = src/mini/cd.c src/mini/echo.c src/mini/env.c src/mini/export.c src/mini/pwd.c src/mini/unset.c src/mini/exit.c

PATH_SRC = src/path/cmd-pather.c src/path/path-simplifier.c src/path/simplifier-extra.c

TOKEN_SRC = src/tokenizer/tokenizer.c src/tokenizer/checker.c src/tokenizer/syntaxer.c \
			src/tokenizer/expander.c src/tokenizer/checker-utils.c src/tokenizer/expander-utils.c \
			src/tokenizer/tokenizer-cmd.c src/tokenizer/tokenizer-extra.c src/tokenizer/tokenizer-split.c\
			src/tokenizer/quoter.c

FILER_SRC = src/tokenizer/filer/filer.c src/tokenizer/filer/filer-next.c src/tokenizer/filer/filer-current.c

EXEC_SRC = src/exec/exec.c src/exec/exec-builtin.c

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
	${CC} ${CFLAGS} ${OBJS} $(HEADERS) ${LIBFT} -g3 -O3 -o ${NAME} -lreadline -L ~/.brew/Cellar/readline/8.2.13/lib

.PHONY: all clean fclean re