#include "src/minishell.h"
#include "stdlib.h"

static int	nwords(char const *s)
{
	int	count;
	int	nword;
	int	i;
	int	qu[2];

	count = 0;
	nword = 1;
	i = -1;
	qu[0] = 0;
	qu[1] = 0;
	while (s[++i])
	{
		if (s[i] == '"' && !qu[0])
			qu[1] = !qu[1];
		else if (s[i] == '\'' && !qu[1])
			qu[0] = !qu[0];
		if (!ft_strchr(" \t\n", s[i]) && nword)
		{
			count++;
			nword = 0;
		}
		if (ft_strchr(" \t\n", s[i]) && !(qu[0] || qu[1]) && !nword)
			nword = 1;
	}
	return (count);
}

static int	wordlen(char const *s, int ind)
{
	int	count;
	int	qu[2];

	count = 0;
	qu[0] = 0;
	qu[1] = 0;
	while ((!ft_strchr(" \t\n", s[ind]) || qu[0] || qu[1]) && s[ind])
	{
		if (s[ind] == '"' && !qu[0])
			qu[1] = !qu[1];
		else if (s[ind] == '\'' && !qu[1])
			qu[0] = !qu[0];
		count++;
		ind++;
	}
	return (count);
}

static void	*freem(char **str, int a)
{
	int	i;

	i = -1;
	while (str[++i] && i < a)
		free(str[i]);
	free(str);
	return ((void *)0);
}

static char	**split_process(char const *s, char **res)
{
	int	nword;
	int	i;
	int	a;

	nword = 1;
	i = -1;
	a = -1;
	while (s[++a])
	{
		if (!ft_strchr(" \t\n", s[a]) && nword)
		{
			res[++i] = (char *)malloc(wordlen(s, a) + 1);
			if (!(res[i]))
				return (freem(res, i));
			ft_strlcpy(res[i], s + a, wordlen(s, a) + 1);
			a = a + wordlen(s, a) - 1;
		}
		nword = (ft_strchr(" \t\n", s[a]) != 0) ;
	}
	res[++i] = (void *)0;
	return (res);
}

char	**splitline(char const *s)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc((nwords(s) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (split_process(s, res));
}

int main(int argc, char **argv) {
	if (argc != 2)
		return 1;
	char **ret = splitline(argv[1]);
	printf("[ ");
	for (int i = 0; ret[i]; i++)
	{
		printf("\"%s\"", ret[i]);
		if (ret[i + 1])
			printf(", ");
	}
	printf(" ]\n");
}