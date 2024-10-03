/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer-current.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:46:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 21:53:37 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filer.h"

char	*ft_strndup(char *str, int n)
{
	char	*ret;
	int		i;

	ret = ft_malloc(n + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < n)
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

char	*stromit(char *str, int start, int len)
{
	char	*ret;
	int		i;

	ret = ft_malloc(ft_strlen(str) - len + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < start)
		ret[i] = str[i];
	i--;
	while (str[++i + len])
		ret[i] = str[i + len];
	ret[i] = 0;
	return (ret);
}

int	remfromcurrent(t_cmd *cmd, int *i, int *j, int k)
{
	char	*tmp;

	(*j)--;
	k++;
	if (*j > 0 && ft_strchr("<>", cmd->argv[*i][*j - 1]))
	{
		(*j)--;
		k++;
	}
	if (*j == 0 && !cmd->argv[*i][k])
	{
		if (!strarrpop(cmd, *i))
			return (0);
	}
	else
	{
		tmp = stromit(cmd->argv[*i], *j, k);
		if (!tmp)
			return (0);
		ft_free(cmd->argv[*i]);
		cmd->argv[*i] = tmp;
	}
	return (1);
}

char	*getredirfromcurrent(t_cmd *cmd, int *i, int *j)
{
	char	*ret;
	int		k;
	int		qu[2];

	k = -1;
	(*j)++;
	if (!cmd->argv[*i] || ft_strchr("&<>()", cmd->argv[*i][*j]))
		return (NULL);
	ft_memset(qu, 0, sizeof(int) * 2);
	while (cmd->argv[*i][++k + *j])
	{
		if (cmd->argv[*i][k + *j] == '\'' && !qu[1])
			qu[0] = !qu[0];
		if (cmd->argv[*i][k + *j] == '"' && !qu[0])
			qu[1] = !qu[1];
		if (!qu[0] && !qu[1] && ft_strchr("<>", cmd->argv[*i][k + *j]))
			break ;
	}
	ret = ft_substr(cmd->argv[*i], *j, k);
	if (!ret)
		return (NULL);
	if (!remfromcurrent(cmd, i, j, k))
		return (ft_free(ret), NULL);
	return (ret);
}
