/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:42:03 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/08 17:58:02 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getcmdli(t_prog *prog)
{
	char	*line;

	while (1)
	{
		line = ft_readline(prog);
		if (!line)
			return (printf("exit\n"), freeprog(prog), 0);
		if (!*line)
		{
			if (line)
				ft_free(prog, line);
			continue ;
		}
		prog->cmdli = tokenize(prog, line);
		if (!prog->cmdli)
			continue ;
		return (1);
	}
}

int	openfds(t_prog *prog)
{
	int	i;
	int	togg;

	i = -1;
	togg = 0;
	while (++i < prog->cmdli->nbcmds)
	{
		if (!openfd(prog, prog->cmdli->cmds[i]))
		{
			while (i < prog->cmdli->nbcmds)
				ft_free(prog, prog->cmdli->cmds[i++]);
			ft_free(prog, prog->cmdli->cmds);
			ft_free(prog, prog->cmdli);
			togg = 1;
			break ;
		}
	}
	return (!togg);
}

int	runprog(t_prog *prog, int i, int j)
{
	int	status;

	i = 0;
	while (i < prog->cmdli->nbcmds)
	{
		if (checkbuiltin(prog->cmdli->cmds[i])
			&& prog->cmdli->nbcmds == 1)
			status = cmdbuiltin(prog, prog->cmdli, i);
		else
			status = cmd(prog, prog->cmdli, i);
		if (!status)
			return (1);
		i++;
	}
	j = -1;
	while (++j < i && !(checkbuiltin(prog->cmdli->cmds[0]) && prog->cmdli->nbcmds == 1))
	{
		waitpid(prog->cmdli->cmds[j]->pid, &status, 0);
		if (prog->cmdli->cmds[j]->pid == prog->cmdli->lastpid)
			setstatus(status);
		closefd(prog->cmdli->cmds[j]->fd);
	}
	return (1);
}

int	resetloop(t_prog *prog, int stds[2])
{
	prog->status = ST_IDLE;
	if (dup2(stds[0], STDIN_FILENO) == -1)
		return (printf("%d\n", stds[0]), 0);
	if (dup2(stds[1], STDOUT_FILENO) == -1)
		return (0);
	close(stds[0]);
	close(stds[1]);
	if (g_interupt == 130 || g_interupt == 131)
		printf("\n");
	signal(SIGQUIT, SIG_IGN);
	if (prog->cmdli)
		freecmdli(prog, prog->cmdli);
	stds[0] = dup(STDIN_FILENO);
	if (stds[0] == -1)
		return (0);
	stds[1] = dup(STDOUT_FILENO);
	if (stds[1] == -1)
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		stds[2];
	int		j;
	t_prog	prog;

	if (!argc && !argv && !envp)
		return (1);
	i = 0;
	j = 0;
	if (!initprog(&prog, envp, stds))
		return (write(2, "mishell: Init error\n", 20));
	while (1)
	{
		if (!getcmdli(&prog))
			return (0);
		if (!openfds(&prog))
			continue ;
		signal(SIGQUIT, sighandler);
		if (!runprog(&prog, i, j))
			return (freeprog(&prog), 0);
		if (!resetloop(&prog, stds))
			return (freeprog(&prog), 0);
	}
	return (0);
}
