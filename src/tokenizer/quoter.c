/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:18:57 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 15:59:17 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbchars(char *str)
{
	int	qu[2];
	int	i;
	int	c;

	ft_memset(qu, 0, sizeof(int) * 2);
	i = -1;
	c = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !qu[1])
		{
			qu[0] = !qu[0];
			continue ;
		}
		if (str[i] == '"' && !qu[0])
		{
			qu[1] = !qu[1];
			continue ;
		}
		c++;
	}
	return (c);
}

void	dothat(char *og, char *new)
{
	int	qu[2];
	int	i;
	int	j;

	ft_memset(qu, 0, sizeof(int) * 2);
	i = -1;
	j = -1;
	while (++j > -1 && og[++i])
	{
		if (og[i] == '\'' && !qu[1])
		{
			qu[0] = !qu[0];
			j--;
			continue ;
		}
		if (og[i] == '"' && !qu[0])
		{
			qu[1] = !qu[1];
			j--;
			continue ;
		}
		new[j] = og[i];
	}
	new[j] = 0;
}

int	remquotes(t_prog *prog, t_cmd *cmd)
{
	int		i;
	char	*tmp;
	int		qu[2];

	i = -1;
	while (cmd->argv[++i])
	{
		ft_memset(qu, 0, sizeof(int) * 2);
		tmp = cmd->argv[i];
		cmd->argv[i] = ft_malloc(prog,
				sizeof(char) * (nbchars(cmd->argv[i]) + 1));
		if (!cmd->argv[i])
			return (0);
		dothat(tmp, cmd->argv[i]);
		ft_free(prog, tmp);
	}
	return (1);
}
