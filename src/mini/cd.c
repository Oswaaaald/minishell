/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:35:04 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 16:03:50 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_malloc(strlen(s1) + strlen(s2) + 1);
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

int	updatepwd(char *new, char *old)
{
	char	*tmpnew;
	char	*tmpold;

	tmpnew = ft_strjoin("PWD=", new);
	if (!tmpnew)
		return (1);
	tmpold = ft_strjoin("OLDPWD=", old);
	if (!tmpold)
		return (ft_free(tmpnew), 1);
	if (!ft_setenv(tmpnew))
		return (ft_free(tmpnew), 1);
	if (!ft_setenv(tmpold))
		return (ft_free(tmpnew), ft_free(tmpold), 1);
	return (0);
}

int	cdback()
{
	char	*buff;

	buff = ft_strdup(ft_getenv("PWD"));
	if (!buff)
		return (1);
	if (chdir(ft_getenv("OLDPWD")) == -1)
		return (perror("mishell: cd"), ft_free(buff), 1);
	if (updatepwd(ft_getenv("OLDPWD"), buff))
		return (ft_free(buff), 1);
	ft_free(prog.cwd);
	prog.cwd = ft_strdup(ft_getenv("PWD"));
	if (!prog.cwd)
		return (ft_free(buff), 1);
	return (ft_free(buff), 0);
}

int	minicd(char **args)
{
	char	*buff;

	if (args[1] && ((args[2] && ft_strncmp(args[1], "--", -1))
		|| (!ft_strncmp(args[1], "--", -1) && args[3])))
	{
		write(STDERR_FILENO, "mishell: cd: too many arguments\n", 33);
		return (1);
	}
	else if (args[1] && !ft_strncmp(args[1], "--", -1))
		buff = parsepath(args[2]);
	else
		buff = parsepath(args[1]);
	if (!buff)
		return (0);
	if (!ft_strncmp(buff, "/-", -1))
		return (ft_free(buff), cdback(prog));
	if (chdir(buff) == -1)
		return (perror("mishell: cd"), ft_free(buff), 1);
	ft_free(prog.cwd);
	prog.cwd = buff;
	if (updatepwd(buff, ft_getenv("PWD")))
		return (1);
	return (0);
}
