/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:42:03 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 21:34:22 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getcmdli(void)
{
	char	*line;

	while (1)
	{
		line = ft_readline();
		if (!line && !g_prog.interupt)
			return (printf("exit\n"), freeprog(), 0);
		if ((!line && g_prog.interupt) || !*line)
		{
			if (line)
				ft_free(line);
			continue ;
		}
		g_prog.cmdli = tokenize(line);
		if (!g_prog.cmdli)
			continue ;
		return (1);
	}
}

int	openfds(int stds[2])
{
	int	i;
	int	togg;

	i = -1;
	togg = 0;
	while (++i < g_prog.cmdli->nbcmds)
	{
		if (!openfd(g_prog.cmdli->cmds[i]))
		{
			closefd(stds);
			while (i < g_prog.cmdli->nbcmds)
				ft_free(g_prog.cmdli->cmds[i++]);
			ft_free(g_prog.cmdli->cmds);
			ft_free(g_prog.cmdli);
			togg = 1;
			break ;
		}
	}
	return (!togg);
}

int	runprog(int i, int j)
{
	int	status;

	i = 0;
	g_prog.status = ST_RUN;
	while (i < g_prog.cmdli->nbcmds)
	{
		if (checkbuiltin(g_prog.cmdli->cmds[i])
			&& g_prog.cmdli->nbcmds == 1)
			cmdbuiltin(g_prog.cmdli, i);
		else
		{
			if (!cmd(g_prog.cmdli, i))
				return (0);
		}
		i++;
	}
	j = -1;
	while (++j < i)
	{
		waitpid(g_prog.cmdli->cmds[j]->pid, &status, 0);
		if (g_prog.cmdli->cmds[j]->pid == g_prog.cmdli->lastpid)
			setstatus(status);
		closefd(g_prog.cmdli->cmds[j]->fd);
	}
	return (1);
}

void	resetloop(int stds[2])
{
	g_prog.status = ST_IDLE;
	dup2(stds[0], STDIN_FILENO);
	dup2(stds[1], STDOUT_FILENO);
	close(stds[0]);
	close(stds[1]);
	if (g_prog.interupt && g_prog.lastexit)
		printf("\n");
	freecmdli(g_prog.cmdli);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		stds[2];
	int		j;

	if (!argc && !argv && !envp)
		return (1);
	i = 0;
	j = 0;
	if (!initprog(envp))
		return (write(2, "mishell: Init error\n", 20));
	while (1)
	{
		stds[0] = dup(STDIN_FILENO);
		stds[1] = dup(STDOUT_FILENO);
		if (!getcmdli())
			return (0);
		if (!openfds(stds))
			continue ;
		if (!runprog(i, j))
			return (0);
		resetloop(stds);
	}
	return (0);
}
