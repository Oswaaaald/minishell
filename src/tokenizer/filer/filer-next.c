/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer-next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:43:02 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 23:09:36 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filer.h"

int	strarrpop(t_cmd *cmd, int i)
{
	int		j;
	char	**tmp;
	int		togg;

	j = -1;
	while (cmd->argv[++j])
		;
	tmp = ft_malloc(sizeof(char *) * (j));
	if (!tmp)
		return (0);
	j = -1;
	togg = 0;
	while (cmd->argv[++j])
	{
		if (i == j)
			togg = 1;
		if (i == j)
			continue ;
		tmp[j - togg] = cmd->argv[j];
	}
	tmp[j - togg] = NULL;
	ft_free(cmd->argv);
	cmd->argv = tmp;
	return (1);
}

int	remlastmeta(t_cmd *cmd, int i)
{
	int		j;
	char	*ret;

	j = ft_strlen(cmd->argv[i]) - 1;
	if (ft_strchr("<>", cmd->argv[i][j - 1]))
		j--;
	cmd->argv[i][j] = 0;
	ret = ft_strdup(cmd->argv[i]);
	if (!ret)
		return (0);
	cmd->argv[i][j] = '<';
	ft_free(cmd->argv[i]);
	cmd->argv[i] = ret;
	return (1);
}

int	remfromnexter(t_cmd *cmd, int *i)
{
	if ((ft_strchr("<>", cmd->argv[*i - 1][0]) && !cmd->argv[*i - 1][1]) ||
		(ft_strchr("<>", cmd->argv[*i - 1][0]) &&
		ft_strchr("<>", cmd->argv[*i - 1][1]) && !cmd->argv[*i - 1][2]))
	{
		if (!strarrpop(cmd, *i - 1))
			return (0);
	}
	else
	{
		if (!remlastmeta(cmd, *i - 1))
			return (0);
		return (1);
	}
	(*i)--;
	return (1);
}

int	remfromnext(t_cmd *cmd, int *i, int k)
{
	char	*tmp;

	if (!cmd->argv[*i][k])
	{
		if (!strarrpop(cmd, *i))
			return (0);
	}
	else
	{
		tmp = ft_strdup(cmd->argv[*i] + k);
		if (!tmp)
			return (0);
		ft_free(cmd->argv[*i]);
		cmd->argv[*i] = tmp;
	}
	return (remfromnexter(cmd, i));
}

char	*getredirfromnext(t_cmd *cmd, int *i, int *j)
{
	char	*ret;
	int		k;
	int		qu[2];

	k = -1;
	(*i)++;
	if (!cmd->argv[*i] || ft_strchr("&<>()", cmd->argv[*i][0]))
		return (printf("%s%c'", LONGSTR, cmd->argv[*i][0]), NULL);
	ft_memset(qu, 0, sizeof(int) * 2);
	while (cmd->argv[*i][++k])
	{
		if (cmd->argv[*i][k] == '\'' && !qu[1])
			qu[0] = !qu[0];
		if (cmd->argv[*i][k] == '"' && !qu[0])
			qu[1] = !qu[1];
		if (!qu[0] && !qu[1] && ft_strchr("<>", cmd->argv[*i][k]))
			break ;
	}
	ret = ft_substr(cmd->argv[*i], 0, k);
	if (!ret)
		return (NULL);
	if (!remfromnext(cmd, i, k))
		return (ft_free(ret), NULL);
	*j = 0;
	return (ret);
}
