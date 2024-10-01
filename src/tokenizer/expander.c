/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:42:21 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 17:36:59 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	translationorwhatevahhandler(char **buff, char *str, int i)
{
	char	*tmp;

	if (i == 0)
		return (1);
	str[i] = 0;
	if (!*buff)
		*buff = ft_strdup(str);
	else
	{
		tmp = *buff;
		*buff = ft_strjoin(*buff, str);
		ft_free(tmp);
	}
	str[i] = '$';
	return (i + 1);
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
	while (str[++i])
	{
		if (str[i] == '?' && si == i - 1)
		{
			i++;
			break ;
		}
		if ((i == si + 1 && !(ft_isalpha(str[i]) || str[i] == '_'))
			|| (i > 0 && !(ft_isalnum(str[i]) || str[i] == '_')))
		{
			break ;
		}
	}
	c = str[i];
	if (si == i - 1 && !ft_isdigit(str[i]))
	{
		tmp = *buff;
		*buff = ft_strjoin(*buff, "$");
		ft_free(tmp);
		return (i);
	}
	else if (si == i - 1 && ft_isdigit(str[i]))
		return (i + 1);
	str[i] = '\0';
	if (ft_getenv(&str[si + 1]))
		*buff = ft_strjoin(*buff, ft_getenv(&str[si + 1]));
	str[i] = c;
	return (i);
}

char	*expand(char *str)
{
	int		i;
	char	*buff;
	int		quotes[2];
	int		last;

	i = -1;
	buff = NULL;
	quotes[0] = 0;
	quotes[1] = 0;
	last = 0;
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
