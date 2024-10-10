/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:42:21 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/10 13:59:37 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updatequotes(int quotes[2], char c)
{
	if (c == '"' && !quotes[0])
		quotes[1] = !quotes[1];
	if (c == '\'' && !quotes[1])
		quotes[0] = !quotes[0];
}

int	expandvarer(t_prog *prog, char *str, int i[2], char **buff)
{
	char	c;

	c = str[i[0]];
	if (i[1] == i[0] - 1 && ft_isdigit(str[i[0]]))
		return (i[0] + 1);
	str[i[0]] = '\0';
	if (ft_getenv(prog, &str[i[1] + 1]))
		*buff = ft_strjoin(prog, *buff, ft_getenv(prog, &str[i[1] + 1]));
	str[i[0]] = c;
	return (i[0]);
}

int	expandvar(t_prog *prog, char **buff, char *str, int i)
{
	int		si;
	char	*tmp;
	//char	c;

	si = i;
	str[i] = '\0';
	if (!*buff)
		*buff = ft_strdup(prog, str);
	else
	{
		tmp = *buff;
		*buff = ft_strjoin(prog, *buff, str);
		ft_free(prog, tmp);
	}
	str[i] = '$';
	i = getendofvar(str, i, si);
	//c = str[i];
	if (si == i - 1 && !ft_isdigit(str[i]))
	{
		tmp = *buff;
		*buff = ft_strjoin(prog, *buff, "$");
		ft_free(prog, tmp);
		return (i);
	}
	return (expandvarer(prog, str, (int [2]){i, si}, buff));
}

char	*expander(t_prog *prog, char *str, int last, char *buff)
{
	int	quotes[2];
	int	i;

	i = -1;
	ft_memset(quotes, 0, sizeof(int) * 2);
	while (str[++i])
	{
		updatequotes(quotes, str[i]);
		if (str[i] == '$' && ft_strchr("\"'", str[i + 1]) && str[i + 1] != 0)
		{
			if (!quotes[0] && !quotes[1])
				last = last + translationorwhatevahhandler(prog, &buff,
						str + last, i - last);
			continue ;
		}
		if (str[i] == '$' && !quotes[0])
		{
			last = last + expandvar(prog, &buff, &(str[last]), i - last);
			i = last - 1;
		}
	}
	if (!buff)
		return (ft_strdup(prog, str));
	return (ft_strjoin(prog, buff, &str[last]));
}

int	expandcmd(t_prog *prog, t_cmd *cmd)
{
	int		i;
	char	*buff;
	int		last;

	i = -1;
	buff = NULL;
	last = 0;
	if (!cmd->argv)
		return (1);
	while (i != -2 && cmd->argv[++i])
		updatestr(prog, &i, &cmd->argv[i],
			expander(prog, cmd->argv[i], last, buff));
	if (cmd->limmiter)
		updatestr(prog, &i, &cmd->limmiter,
			expander(prog, cmd->limmiter, last, buff));
	if (cmd->input)
		updatestr(prog, &i, &cmd->input,
			expander(prog, cmd->input, last, buff));
	if (cmd->output)
		updatestr(prog, &i, &cmd->output,
			expander(prog, cmd->output, last, buff));
	if (i == -2)
		return (0);
	return (1);
}
