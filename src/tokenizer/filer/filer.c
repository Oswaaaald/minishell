/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:58:39 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/10 14:01:57 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "filer.h"

void	setredirser(t_prog *prog, t_cmd *cmd, char *str, char *metachar)
{
	if (cmd->output)
		ft_free(prog, cmd->output);
	cmd->output = str;
	if (metachar[1] == '>')
		openoutput(cmd, str, 1);
	else
		openoutput(cmd, str, 0);
}

void	setredirs(t_prog *prog, t_cmd *cmd, char *str, char *metachar)
{
	if ((metachar[0] == '<' && metachar[1] != '<')
		|| (metachar[0] == '<' && metachar[1] == '>'))
	{
		if (cmd->input)
			ft_free(prog, cmd->input);
		cmd->input = str;
		if (metachar[1] == '>')
			openinput(cmd, str, 1);
		else
			openinput(cmd, str, 0);
	}
	else if (metachar[0] == '<' && metachar[1] == '<')
	{
		if (cmd->limmiter)
			ft_free(prog, cmd->limmiter);
		cmd->limmiter = str;
		openhd(prog, cmd, str);
	}
	else if (metachar[0] == '>')
		setredirser(prog, cmd, str, metachar);
}

int	getredir(t_prog *prog, t_cmd *cmd, int *i, int *j)
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
		str = getredirfromnext(prog, cmd, i, j);
	else
		str = getredirfromcurrent(prog, cmd, i, j);
	if (!str)
		return (0);
	setredirs(prog, cmd, str, metachar);
	return (1);
}

int	getredirser(t_prog *prog, t_cmd *cmd, int *i, int qu[2])
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
			if (!getredir(prog, cmd, i, &j))
				return (0);
			if (!cmd->argv[*i])
				break ;
			j--;
		}
	}
	return (1);
}

int	getredirs(t_prog *prog, t_cmd *cmd)
{
	int	qu[2];
	int	i;

	ft_memset(qu, 0, sizeof(int) * 2);
	i = -1;
	while (cmd->argv[++i])
	{
		if (!ft_strlen(cmd->argv[i]))
			continue ;
		if (!getredirser(prog, cmd, &i, qu))
			return (0);
		if (!cmd->argv[i])
			break ;
	}
	return (1);
}
