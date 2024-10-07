/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer-current.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:46:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 14:56:31 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filer.h"

char	*ft_strndup(t_prog *prog, char *str, int n)
{
	char	*ret;
	int		i;

	ret = ft_malloc(prog, n + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < n)
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

char	*stromit(t_prog *prog, char *str, int start, int len)
{
	char	*ret;
	int		i;

	ret = ft_malloc(prog, ft_strlen(str) - len + 1);
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

int	remfromcurrent(t_prog *prog, t_cmd *cmd, int *i[2], int k)
{
	char	*tmp;

	(*i[1])--;
	k++;
	if (*i[1] > 0 && ft_strchr("<>", cmd->argv[*i[0]][*i[1] - 1]))
	{
		(*i[1])--;
		k++;
	}
	if (*i[1] == 0 && !cmd->argv[*i[0]][k])
	{
		if (!strarrpop(prog, cmd, *i[0]))
			return (0);
	}
	else
	{
		tmp = stromit(prog, cmd->argv[*i[0]], *i[1], k);
		if (!tmp)
			return (0);
		ft_free(prog, cmd->argv[*i[0]]);
		cmd->argv[*i[0]] = tmp;
	}
	return (1);
}

char	*getredirfromcurrent(t_prog *prog, t_cmd *cmd, int *i, int *j)
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
	ret = ft_substr(prog, cmd->argv[*i], *j, k);
	if (!ret)
		return (NULL);
	if (!remfromcurrent(prog, cmd, (int *[]){i, j}, k))
		return (ft_free(prog, ret), NULL);
	return (ret);
}
