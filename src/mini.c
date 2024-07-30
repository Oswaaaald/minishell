/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:38:28 by fghysbre          #+#    #+#             */
/*   Updated: 2024/07/30 17:05:36 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void    ft_setenv(t_prog *prog, char *var)
{
    int i;
    int eq;

    eq = -1;
    while (var[++eq])
    {
        if (var[eq] == '=')
            break ;
    }
    i = -1;
    while (environ[++i])
    {
        if (!strncmp(environ[i], var, eq))
        {
            if (prog->envmod[i])
                free(environ[i]);
            environ[i] = var;
            prog->envmod[i] = 1;
			return ;
        }
    }
	printf("what is this : %s\n", var);
}

void    cdback(t_prog *prog)
{
    char	*buff;

	buff = ft_strdup(getenv("PWD"));
	if (chdir(getenv("OLDPWD")) == -1)
		perror("mishell: cd");
	ft_setenv(prog, ft_strjoin("PWD=", getenv("OLDPWD")));
	ft_setenv(prog, ft_strjoin("OLDPWD=", buff));
	free(buff);
}

void	minicd(t_prog *prog, char **args)
{
	char	*buff;

	if ((args[2] && ft_strncmp(args[1], "--", -1)) || (!ft_strncmp(args[1], "--", -1) && args[3]))
	{
		write(STDERR_FILENO, "mishell: cd: too many arguments\n", 33);
		return ;
	}
	else if (args[1] && !ft_strncmp(args[1], "--", -1))
		buff = parsepath(args[2]);
	else
		buff = parsepath(args[1]);
    if (!ft_strncmp(buff, "/-", - 1))
	{
		cdback(prog);
		return ;
	}
	if (chdir(buff) == -1 && errno == ENOENT)
		perror("mishell: cd");
    ft_setenv(prog, strjoin("OLDPWD=", getenv("PWD")));
    ft_setenv(prog, strjoin("PWD=", buff));
	free(buff);
}

void	miniecho(char **args)
{
	int	i;
    int flagn;

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
}

void    minipwd()
{
    char    *cwd;

    cwd = getenv("PWD");
    write(STDOUT_FILENO, cwd, strlen(cwd));
    write(STDOUT_FILENO, "\n", 1);
}

void	expshowall()
{
	int	i;

	i = -1;
	while (environ[++i])
		printf("declare -x %s\n", environ[i]);
}

int	miniexport(char **args)
{
	if (!args[1])
		return (expshowall(), 0);
	return (0);
}