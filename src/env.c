/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:29:54 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/08 18:06:26 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_prog *prog, char *s)
{
	int		i;
	char	*res;

	i = -1;
	if (s[0] == '?' && s[1] == 0)
		return (ft_itoa(prog, g_interupt));
	while (prog->minienv[++i])
	{
		if (!ft_strncmp(prog->minienv[i], s, ft_strlen(s))
			&& (prog->minienv[i][ft_strlen(s)] == '='
			|| prog->minienv[i][ft_strlen(s)] == '\0'))
			break ;
	}
	if (!prog->minienv[i])
		return (NULL);
	res = ft_strchr(prog->minienv[i], '=');
	if (res)
		return (++res);
	return (ft_strchr(prog->minienv[i], '\0'));
}

int	ft_addenv(t_prog *prog, char *var)
{
	int		i;
	char	**res;

	i = -1;
	if (prog->minienv)
	{
		while (prog->minienv[++i])
			;
		res = ft_malloc(prog, sizeof(char **) * (i + 2));
	}
	else
		res = ft_malloc(prog, sizeof(char **) * (2));
	if (!res)
		return (0);
	i = -1;
	while (++i >= 0 && prog->minienv && prog->minienv[i])
		res[i] = prog->minienv[i];
	res[i] = var;
	res[++i] = NULL;
	if (prog->minienv)
		ft_free(prog, prog->minienv);
	prog->minienv = res;
	return (1);
}

int	ft_setenv(t_prog *prog, char *var)
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
	while (prog->minienv && prog->minienv[++i])
	{
		if ((ft_strchr(var, '=') && !ft_strncmp(prog->minienv[i], var, eq))
			|| (!ft_strchr(var, '=')
				&& !ft_strncmp(prog->minienv[i], var, ft_strlen(var))
				&& (prog->minienv[i][ft_strlen(var)] == '='
				|| prog->minienv[i][ft_strlen(var)] == '\0')))
		{
			ft_free(prog, prog->minienv[i]);
			prog->minienv[i] = var;
			return (1);
		}
	}
	return (ft_addenv(prog, var));
}

static int	ft_remenver(t_prog *prog, char *s, int i, char **newenv)
{
	int	tog;

	tog = 0;
	while (prog->minienv[++i])
	{
		if (!ft_strncmp(prog->minienv[i], s, ft_strlen(s))
			&& (prog->minienv[i][ft_strlen(s)] == '='
			|| prog->minienv[i][ft_strlen(s)] == '\0'))
		{
			ft_free(prog, prog->minienv[i]);
			tog = 1;
		}
		else
			newenv[i - tog] = prog->minienv[i];
	}
	ft_free(prog, prog->minienv);
	newenv[i - tog] = NULL;
	prog->minienv = newenv;
	return (1);
}

int	ft_remenv(t_prog *prog, char *s)
{
	char	**newenv;
	int		i;

	i = -1;
	while (prog->minienv[++i])
		;
	newenv = (char **) ft_malloc(prog, sizeof(char *) * i);
	if (!newenv)
		return (0);
	i = -1;
	return (ft_remenver(prog, s, i, newenv));
}
