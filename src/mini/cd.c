/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:35:04 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/04 16:00:11 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
