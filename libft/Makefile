SOURCES = ft_atoi.c ft_calloc.c ft_is.c ft_itoa.c ft_mem.c ft_memchr.c ft_memcmp.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_to.c

HEADERS = libft.h

OBJECTS = ${SOURCES:.c=.o}

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

BONUS_SRCS = ${SOURCES} ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

all: ${NAME}

.c.o:
	cc ${CFLAGS} -c -I ./includes/ $< -o ${<:.c=.o}

clean:
	rm -f ${BONUS_OBJS}

fclean: clean
	rm -f libft.a

re: fclean all

${NAME}: ${OBJECTS}
	ar rc ${NAME} ${OBJECTS}
	ranlib ${NAME}

bonus: ${BONUS_OBJS}
	ar rc ${NAME} ${BONUS_OBJS}
	ranlib ${NAME}

.PHONY: all, clean, fclean, re, bonus