/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:38:28 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/02 23:35:45 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	CD

char	*strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(strlen(s1) + strlen(s2) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	i--;
	j = -1;
	while (s2[++j] && ++i)
		ret[i] = s2[j];
	ret[i + 1] = '\0';
	return (ret);
}

void	ft_addenv(t_prog *prog, char *var)
{
	int		i;
	char	**res;

	i = -1;
	while (prog->minienv[++i])
		;
	res = malloc(sizeof(char **) * (i + 2));
	i = -1;
	while (prog->minienv[++i])
		res[i] = prog->minienv[i];
	res[i] = var;
	res[++i] = NULL;
	free(prog->minienv);
	prog->minienv = res;
}

void	ft_setenv(t_prog *prog, char *var)
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
	while (prog->minienv[++i])
	{
		if (!ft_strncmp(prog->minienv[i], var, eq))
		{
			free(prog->minienv[i]);
			prog->minienv[i] = var;
			return ;
		}
	}
	ft_addenv(prog, var);
}

void	cdback(t_prog *prog)
{
	char	*buff;

	buff = ft_strdup(ft_getenv(prog, "PWD"));
	if (chdir(ft_getenv(prog, "OLDPWD")) == -1)
		perror("mishell: cd");
	ft_setenv(prog, ft_strjoin("PWD=", ft_getenv(prog, "OLDPWD")));
	ft_setenv(prog, ft_strjoin("OLDPWD=", buff));
	free(prog->cwd);
	prog->cwd = ft_strdup(ft_getenv(prog, "PWD"));
	free(buff);
}

int	minicd(t_prog *prog, char **args)
{
	char	*buff;

	if ((args[2] && ft_strncmp(args[1], "--", -1))
		|| (!ft_strncmp(args[1], "--", -1) && args[3]))
	{
		write(STDERR_FILENO, "mishell: cd: too many arguments\n", 33);
		return (1);
	}
	else if (args[1] && !ft_strncmp(args[1], "--", -1))
		buff = parsepath(prog, args[2]);
	else
		buff = parsepath(prog, args[1]);
	if (!ft_strncmp(buff, "/-", -1))
	{
		cdback(prog);
		return (0);
	}
	if (chdir(buff) == -1 && errno == ENOENT)
		perror("mishell: cd");
	ft_setenv(prog, strjoin("OLDPWD=", ft_getenv(prog, "PWD")));
	ft_setenv(prog, strjoin("PWD=", buff));
	free(prog->cwd);
	prog->cwd = buff;
	return (0);
}

//	Echo

int	miniecho(char **args)
{
	int	i;
	int	flagn;

	i = 0;
	flagn = 0;
	while (!strcmp(args[++i], "-n"))
		flagn = 1;
	i--;
	while (args[++i])
	{
		write(STDOUT_FILENO, args[i], strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!flagn)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

//	PWD

char	*ft_getenv(t_prog *prog, char *s)
{
	int		i;
	char	*buff;
	char	*res;

	i = -1;
	buff = ft_strjoin(s, "=");
	while (prog->minienv[++i])
	{
		if (!ft_strncmp(prog->minienv[i], buff, ft_strlen(buff)))
			break ;
	}
	free (buff);
	if (!prog->minienv[i])
		return (NULL);
	res = ft_strchr(prog->minienv[i], '=');
	if (res)
		return (++res);
	return (NULL);
}

int	minipwd(t_prog *prog)
{
	write(STDOUT_FILENO, prog->cwd, strlen(prog->cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

//	Export

void	swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

char	**strarrsort(char **arr)
{
	int	i;

	i = 0;
	while (arr[++i])
	{
		if (ft_strncmp(arr[i], arr[i - 1], -1) < 0)
		{
			swap(&arr[i], &arr[i - 1]);
			i = i - 2;
		}
		if (i < 0)
			i = 0;
	}
	return (arr);
}

void	putdeclare(char *s)
{
	int	i;
	int	togg;

	i = -1;
	togg = 0;
	write(STDOUT_FILENO, "declare -x ", 11);
	while (s[++i])
	{
		write(STDOUT_FILENO, &s[i], 1);
		if (s[i] == '=' && !togg)
		{
			write(STDOUT_FILENO, "\"", 1);
			togg = 1;
		}
	}
	if (togg)
		write(STDOUT_FILENO, "\"", 1);
	write(STDOUT_FILENO, "\n", 1);
}

void	expshowall(t_prog *prog)
{
	int		i;
	char	**envdup;

	i = -1;
	envdup = strarrdup(prog->minienv);
	envdup = strarrsort(envdup);
	while (envdup[++i])
		putdeclare(envdup[i]);
}

int	nameisvalid(char *s)
{
	int	i;
	int	togg;

	togg = 0;
	i = -1;
	while (s[++i])
	{
		if (i == 0 && s[i] == '=')
			return (0);
		if (s[i] == '=')
			togg = 1;
		if (i == 0 && !(ft_isalpha(s[i]) || s[i] == '_') && !togg)
			return (0);
		else if (i > 0 && !(ft_isalnum(s[i]) || s[i] == '_') && !togg)
			return (0);
	}
	return (1);
}

int	miniexport(t_prog *prog, char **args)
{
	int	i;
	int	togg;

	if (!args[1])
		return (expshowall(prog), 0);
	i = 0;
	togg = 0;
	while (args[++i])
	{
		if (i == 1 && !ft_strncmp(args[i], "--", -1))
			i++;
		if (i == 1 && args[i][0] == '-')
			return (printf("mishell: export: -%c: invalid option\n"
					args[i][1]), 2);
		else if (!nameisvalid(args[i]))
			printf("mishell: export: %s: not a valid indetifier\n", args[i]);
		else
		{
			ft_setenv(prog, args[i]);
			continue ;
		}
		togg = 1;
	}
	return (togg);
}

// Un-Set

void	ft_remenv(t_prog *prog, char *s)
{
	char	**newenv;
	int		i;
	char	*buff;
	int		tog;

	i = -1;
	tog = 0;
	while (prog->minienv[++i])
		;
	newenv = (char **) malloc(sizeof(char *) * i);
	i = -1;
	buff = ft_strjoin(s, "=");
	while (prog->minienv[++i])
	{
		if (!ft_strncmp(prog->minienv[i], buff, ft_strlen(buff)))
		{
			free(prog->minienv[i]);
			tog = 1;
		}
		else
			newenv[i - tog] = prog->minienv[i];
	}
	free(prog->minienv);
	free(buff);
	newenv[i - tog] = NULL;
	prog->minienv = newenv;
}

int	miniunset(t_prog *prog, char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
			continue ;
		if (ft_getenv(prog, args[i]))
			ft_remenv(prog, args[i]);
	}
	return (1);
}

//	env

int	minienv(t_prog *prog, char **args)
{
	int	i;

	if (args[1])
		return (printf("mishell: env: too many arguments"), 1);
	i = -1;
	while (prog->minienv[++i])
		printf("%s\n", prog->minienv[i]);
	return (1);
}
