/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:19:35 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/13 18:17:42 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//The data that is used to run the shell
typedef struct s_prog
{
	char	lastexit;
	char	*cwd;
	char	**minienv;
	t_list	*mallocs; //<-- pottentiel de fou en sah
}	t_prog;

int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
char				*ft_itoa(t_prog *prog, int n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(t_prog *prog, char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(t_prog *prog, const char *s1);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(t_prog *prog, char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(t_prog *prog, char const *s1, char const *set);
char				*ft_substr(t_prog *prog, char const *s, unsigned int start,
						size_t len);
int					ft_toupper(int c);
int					ft_tolower(int c);

// Bonus
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_prog *prog, t_list *lst,
						void (*del)(t_prog *, void *));
void				ft_lstclear(t_prog *prog, t_list **lst,
						void (*del)(t_prog *, void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_prog *prog, t_list *lst, void *(*f)(void *),
						void (*del)(t_prog *, void *));
void				ft_lstpop(t_prog *prog, t_list **list, t_list *elem);
t_list				*lstbef(t_list *list, t_list *elem);


//Memory
void	ft_free(t_prog *prog, void *ptr);
void	*ft_malloc(t_prog *prog, size_t size);
void	ft_malloc_add_ptr(t_prog *prog, void *ptr);

#endif
