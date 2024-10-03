/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:29:54 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:34:35 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *s)
{
	int		i;
	char	*res;

	i = -1;
	if (!g_prog.minienv)
		return (NULL);
	if (s[0] == '?' && s[1] == 0)
		return (ft_itoa(g_prog.lastexit));
	while (g_prog.minienv[++i])
	{
		if (!ft_strncmp(g_prog.minienv[i], s, ft_strlen(s))
			&& (g_prog.minienv[i][ft_strlen(s)] == '='
			|| g_prog.minienv[i][ft_strlen(s)] == '\0'))
			break ;
	}
	if (!g_prog.minienv[i])
		return (NULL);
	res = ft_strchr(g_prog.minienv[i], '=');
	if (res)
		return (++res);
	return (ft_strchr(g_prog.minienv[i], '\0'));
}

int	ft_addenv(char *var)
{
	int		i;
	char	**res;

	i = -1;
	if (g_prog.minienv)
	{
		while (g_prog.minienv[++i])
			;
		res = ft_malloc(sizeof(char **) * (i + 2));
	}
	else
		res = ft_malloc(sizeof(char **) * (2));
	if (!res)
		return (0);
	i = -1;
	while (++i >= 0 && g_prog.minienv && g_prog.minienv[i])
		res[i] = g_prog.minienv[i];
	res[i] = var;
	res[++i] = NULL;
	if (g_prog.minienv)
		ft_free(g_prog.minienv);
	g_prog.minienv = res;
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
	while (g_prog.minienv && g_prog.minienv[++i])
	{
		if ((ft_strchr(var, '=') && !ft_strncmp(g_prog.minienv[i], var, eq))
			|| (!ft_strchr(var, '=') 
				&& !ft_strncmp(g_prog.minienv[i], var, ft_strlen(var))
				&& (g_prog.minienv[i][ft_strlen(var)] == '='
				|| g_prog.minienv[i][ft_strlen(var)] == '\0')))
		{
			ft_free(g_prog.minienv[i]);
			g_prog.minienv[i] = var;
			return (1);
		}
	}
	return (ft_addenv(var));
}

static int	ft_remenver(char *s, int i, int tog, char **newenv)
{
	while (g_prog.minienv[++i])
	{
		if (!ft_strncmp(g_prog.minienv[i], s, ft_strlen(s))
			&& (g_prog.minienv[i][ft_strlen(s)] == '='
			|| g_prog.minienv[i][ft_strlen(s)] == '\0'))
		{
			ft_free(g_prog.minienv[i]);
			tog = 1;
		}
		else
			newenv[i - tog] = g_prog.minienv[i];
	}
	ft_free(g_prog.minienv);
	newenv[i - tog] = NULL;
	g_prog.minienv = newenv;
	return (1);
}

int	ft_remenv(char *s)
{
	char	**newenv;
	int		i;
	int		tog;

	i = -1;
	tog = 0;
	while (g_prog.minienv[++i])
		;
	newenv = (char **) ft_malloc(sizeof(char *) * i);
	if (!newenv)
		return (0);
	i = -1;
	return (ft_remenver(s, i, tog, newenv));
}
