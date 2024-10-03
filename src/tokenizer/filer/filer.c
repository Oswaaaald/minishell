/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:58:39 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 22:21:42 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "filer.h"

void	setredirser(t_cmd *cmd, char *str, char *metachar)
{
	if (cmd->output)
		ft_free(cmd->output);
	cmd->output = str;
	if (metachar[1] == '>')
		cmd->outappend = 1;
	else
		cmd->outappend = 0;
}

void	setredirs(t_cmd *cmd, char *str, char *metachar)
{
	if ((metachar[0] == '<' && metachar[1] != '<')
		|| (metachar[0] == '<' && metachar[1] == '>'))
	{
		if (cmd->input)
			ft_free(cmd->input);
		cmd->input = str;
		if (cmd->limmiter)
		{
			ft_free(cmd->limmiter);
			cmd->limmiter = NULL;
		}
	}
	else if (metachar[0] == '<' && metachar[1] == '<')
	{
		if (cmd->limmiter)
			ft_free(cmd->limmiter);
		cmd->limmiter = str;
		if (cmd->input)
		{
			ft_free(cmd->input);
			cmd->input = NULL;
		}
	}
	else if (metachar[0] == '>')
		setredirser(cmd, str, metachar);
}

int	getredir(t_cmd *cmd, int *i, int *j)
{
	int		oldj;
	int		oldi;
	char	metachar[2];
	char	*str;

	oldj = *j;
	oldi = *i;
	metachar[0] = cmd->argv[oldi][oldj];
	metachar[1] = cmd->argv[oldi][oldj + 1];
	if (cmd->argv[*i][*j + 1] && ft_strchr("<>", cmd->argv[*i][*j + 1]))
		*j = *j + 1;
	if (!cmd->argv[*i][*j + 1])
		str = getredirfromnext(cmd, i, j);
	else
		str = getredirfromcurrent(cmd, i, j);
	if (!str)
		return (0);
	setredirs(cmd, str, metachar);
	return (1);
}

int	getredirser(t_cmd *cmd, int *i, int qu[2])
{
	int	j;

	j = -1;
	while (cmd->argv[*i][++j])
	{
		if (cmd->argv[*i][j] == '\'' && !qu[1])
			qu[0] = !qu[0];
		if (cmd->argv[*i][j] == '"' && !qu[0])
			qu[1] = !qu[1];
		if (!qu[0] && !qu[1] && ft_strchr("<>", cmd->argv[*i][j]))
		{
			if (!getredir(cmd, i, &j))
				return (0);
			if (!cmd->argv[*i])
				break ;
			j--;
		}
	}
	return (1);
}

int	getredirs(t_cmdli *cmdli, t_cmd *cmd)
{
	int	qu[2];
	int	i;

	ft_memset(qu, 0, sizeof(int) * 2);
	i = -1;
	while (cmd->argv[++i])
	{
		if (!getredirser(cmd, &i, qu))
			return (0);
		if (!cmd->argv[i])
			break ;
	}
	if (checkfiles(cmdli) || !cmd->argv[0])
		return (0);
	return (1);
}
