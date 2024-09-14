/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini-deprecated.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:38:28 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/13 17:30:35 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	CD

/* char	*strjoin(char *s1, char *s2)
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

void	cdback(t_prog *prog)
{
	char	*buff;

	buff = ft_strdup(prog, ft_getenv(prog, "PWD"));
	if (chdir(ft_getenv(prog, "OLDPWD")) == -1)
		perror("mishell: cd");
	ft_setenv(prog, ft_strjoin("PWD=", ft_getenv(prog, "OLDPWD")));
	ft_setenv(prog, ft_strjoin("OLDPWD=", buff));
	free(prog->cwd);
	prog->cwd = ft_strdup(prog, ft_getenv(prog, "PWD"));
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
} */

//	Echo

/* int	miniecho(char **args)
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
} */

//	PWD

/* int	minipwd(t_prog *prog)
{
	write(STDOUT_FILENO, prog->cwd, strlen(prog->cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
} */

//	Export

/* void	swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

char	**strarrsort(char **arr)
{
	int	i;
	char *temp;

	i = 0;
	while (arr[++i])
	{
		if (ft_strncmp(arr[i], arr[i - 1], -1) < 0)
		{
			temp = arr[i];
			arr[i] = arr[i - 1];
			arr[i - 1] = temp;
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
			return (printf("mishell: export: -%c: invalid option\n",
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
} */

// Un-Set

/* int	miniunset(t_prog *prog, char **args)
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
} */

//	env

/* int	minienv(t_prog *prog, char **args)
{
	int	i;

	if (args[1])
		return (printf("mishell: env: too many arguments"), 1);
	i = -1;
	while (prog->minienv[++i])
		printf("%s\n", prog->minienv[i]);
	return (1);
} */
