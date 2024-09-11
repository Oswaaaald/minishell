/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:35:04 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/11 14:20:26 by mleonet          ###   ########.fr       */
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

int	updatepwd(t_prog *prog, char *new, char *old)
{
	char	*tmpnew;
	char	*tmpold;

	tmpnew = ft_strjoin("PWD=", new);
	if (!tmpnew)
		return (1);
	if (!ft_setenv(prog, tmpnew))
		return (free(tmpnew), 1);
	tmpold = ft_strjoin("OLDPWD=", old);
	if (!tmpold)
		return (free(tmpnew), 1);
	if (!ft_setenv(prog, tmpold))
		return (free(tmpnew), free(tmpold), 1);
	return (free(tmpnew), free(tmpold), 0);
}

int	cdback(t_prog *prog)
{
	char	*buff;

	buff = ft_strdup(ft_getenv(prog, "PWD"));
	if (!buff)
		return (1);
	if (chdir(ft_getenv(prog, "OLDPWD")) == -1)
		return (perror("mishell: cd"), free(buff), 1);
	if (updatepwd(prog, ft_getenv(prog, "OLDPWD"), buff))
		return (free(buff), 1);
	free(prog->cwd);
	prog->cwd = ft_strdup(ft_getenv(prog, "PWD"));
	if (!prog->cwd)
		return (free(buff), 1);
	return (free(buff), 0);
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
	if (!buff)
		return (0);
	if (!ft_strncmp(buff, "/-", -1))
		return (free(buff), cdback(prog));
	if (chdir(buff) == -1)
		return (perror("mishell: cd"), free(buff), 1);
	free(prog->cwd);
	prog->cwd = buff;
	if (updatepwd(prog, buff, ft_getenv(prog, "PWD")))
		return (free(buff), 1);
	return (0);
}
