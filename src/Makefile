SRC = main.c

HEADERS = minishell.h

OBJS = ${SRC:.c=.o}

CC = cc

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -g3 -c $< -o ${<:.c=.o}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -g3 -o ${NAME} -lreadline