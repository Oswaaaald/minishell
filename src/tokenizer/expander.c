/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:42:21 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 22:31:28 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getendofvar(char *str, int i, int si)
{
	while (str[++i])
	{
		if (str[i] == '?' && si == i - 1)
		{
			i++;
			break ;
		}
		if ((i == si + 1 && !(ft_isalpha(str[i]) || str[i] == '_'))
			|| (i > 0 && !(ft_isalnum(str[i]) || str[i] == '_')))
			break ;
	}
	return (i);
}

int	expandvarer(char c, char *str, int i[2], char **buff)
{
	if (i[1] == i[0] - 1 && ft_isdigit(str[i[0]]))
		return (i[0] + 1);
	str[i[0]] = '\0';
	if (ft_getenv(&str[i[1] + 1]))
		*buff = ft_strjoin(*buff, ft_getenv(&str[i[1] + 1]));
	str[i[0]] = c;
	return (i[0]);
}

int	expandvar(char **buff, char *str, int i)
{
	int		si;
	char	*tmp;
	char	c;

	si = i;
	str[i] = '\0';
	if (!*buff)
		*buff = ft_strdup(str);
	else
	{
		tmp = *buff;
		*buff = ft_strjoin(*buff, str);
		ft_free(tmp);
	}
	str[i] = '$';
	i = getendofvar(str, i, si);
	c = str[i];
	if (si == i - 1 && !ft_isdigit(str[i]))
	{
		tmp = *buff;
		*buff = ft_strjoin(*buff, "$");
		ft_free(tmp);
		return (i);
	}
	return (expandvarer(c, str, (int [2]){i, si}, buff));
}

char	*expander(char *str, int i, int last, char *buff)
{
	int	quotes[2];

	ft_memset(quotes, 0, sizeof(int) * 2);
	while (str[++i])
	{
		if (str[i] == '"' && !quotes[0])
			quotes[1] = !quotes[1];
		if (str[i] == '\'' && !quotes[1])
			quotes[0] = !quotes[0];
		if (str[i] == '$' && ft_strchr("\"'", str[i + 1]) && str[i + 1] != 0)
		{
			if (!quotes[0] && !quotes[1])
				last = last + translationorwhatevahhandler(&buff,
						str + last, i - last);
			continue ;
		}
		if (str[i] == '$' && !quotes[0])
		{
			last = last + expandvar(&buff, &(str[last]), i - last);
			i = last - 1;
		}
	}
	if (!buff)
		return (ft_strdup(str));
	return (ft_strjoin(buff, &str[last]));
}

char	*expand(char *str)
{
	int		i;
	char	*buff;
	int		last;

	i = -1;
	buff = NULL;
	last = 0;
	return (expander(str, i, last, buff));
}
