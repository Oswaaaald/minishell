/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:29:54 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 16:03:08 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *s)
{
	int		i;
	char	*buff;
	char	*res;

	i = -1;
	if (s[0] == '?' && s[1] == 0)
		return (ft_itoa(prog.lastexit));
	buff = ft_strjoin(s, "=");
	if (!buff)
		return (NULL);
	while (prog.minienv[++i])
	{
		if (!ft_strncmp(prog.minienv[i], buff, ft_strlen(buff)))
			break ;
	}
	ft_free(buff);
	if (!prog.minienv[i])
		return (NULL);
	res = ft_strchr(prog.minienv[i], '=');
	if (res)
		return (++res);
	return (NULL);
}

int	ft_addenv(char *var)
{
	int		i;
	char	**res;

	i = -1;
	while (prog.minienv[++i])
		;
	res = ft_malloc(sizeof(char **) * (i + 2));
	if (!res)
		return (0);
	i = -1;
	while (prog.minienv[++i])
		res[i] = prog.minienv[i];
	res[i] = var;
	res[++i] = NULL;
	ft_free(prog.minienv);
	prog.minienv = res;
	return (1);
}

int	ft_setenv(char *var)
{
	int	i;
	int	eq;

	eq = -1;
	while (var[++eq])
	{
		if (var[eq] == '=')
			break ;
	}
	i = -1;
	while (prog.minienv[++i])
	{
		if (!ft_strncmp(prog.minienv[i], var, eq))
		{
			ft_free(prog.minienv[i]);
			prog.minienv[i] = var;
			return (1);
		}
	}
	ft_addenv(var);
	return (1);
}

int	ft_remenv(char *s)
{
	char	**newenv;
	int		i;
	char	*buff;
	int		tog;

	i = -1;
	tog = 0;
	while (prog.minienv[++i])
		;
	newenv = (char **) ft_malloc(sizeof(char *) * i);
	if (!newenv)
		return (0);
	i = -1;
	buff = ft_strjoin(s, "=");
	while (prog.minienv[++i])
	{
		if (!ft_strncmp(prog.minienv[i], buff, ft_strlen(buff)))
		{
			ft_free(prog.minienv[i]);
			tog = 1;
		}
		else
			newenv[i - tog] = prog.minienv[i];
	}
	ft_free(prog.minienv);
	ft_free(buff);
	newenv[i - tog] = NULL;
	prog.minienv = newenv;
	return (1);
}
