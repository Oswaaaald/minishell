/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:31 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 14:36:36 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbwords(char const *s, char c)
{
	int	count;
	int	nbword;
	int	i;

	count = 0;
	nbword = 1;
	i = -1;
	while (s[++i])
	{
		if (s[i] != c && nbword)
		{
			count++;
			nbword = 0;
		}
		if (s[i] == c && !nbword)
			nbword = 1;
	}
	return (count);
}

static int	wordlen(char const *s, char c, int ind)
{
	int	count;

	count = 0;
	while (s[ind] != c && s[ind])
	{
		count++;
		ind++;
	}
	return (count);
}

static void	*freem(t_prog *prog, char **str, int a)
{
	int	i;

	i = -1;
	while (str[++i] && i < a)
		ft_free(prog, str[i]);
	ft_free(prog, str);
	return ((void *)0);
}

static char	**split_process(t_prog *prog, char const *s, char c)
{
	int		nbword;
	int		i;
	int		a;
	char	**res;

	nbword = 1;
	i = -1;
	a = -1;
	res = (char **)ft_malloc(prog, (nbwords(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (s[++a])
	{
		if (s[a] != c && nbword)
		{
			res[++i] = (char *)ft_malloc(prog, wordlen(s, c, a) + 1);
			if (!(res[i]))
				return (freem(prog, res, i));
			ft_strlcpy(res[i], s + a, wordlen(s, c, a) + 1);
			a = a + wordlen(s, c, a) - 1;
		}
		nbword = (s[a] == c);
	}
	res[++i] = (void *)0;
	return (res);
}

char	**ft_split(t_prog *prog, char const *s, char c)
{
	if (!s)
		return (NULL);
	return (split_process(prog, s, c));
}

/* #include <stdio.h>

int	main(void)
{
	char	**res;
	int		i;
	char	*s;
	char	c;

	s = "nonempty";
	c = 0;
	res = ft_split(s, c);
	i = -1;
	if (!res)
		return (1);
	while (res[++i])
		printf("%s\n", res[i]);
} */