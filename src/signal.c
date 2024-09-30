/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:27:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/30 17:39:03 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredocsighandler(int sig)
{
	if (!sig)
		return ;
	close(STDIN_FILENO);
}

void	sighandler(int sig)
{
	int	i;

	i = -1;
	g_prog.interupt = sig;
	close(STDIN_FILENO);
	if (g_prog.heredocpid)
	{
		kill(g_prog.heredocpid, sig);
		printf("\n");
	}
	else if (g_prog.cmdli)
	{
		while (g_prog.cmdli->cmds[++i])
		{
			if (!g_prog.cmdli->cmds[i]->pid)
				continue ;
			if (kill(g_prog.cmdli->cmds[i]->pid, sig) == -1)
				printf("mishell: failed to kill process with pid: %d\n",
					g_prog.cmdli->cmds[i]->pid);
		}
		printf("\n");
		rl_on_new_line();
	}
	else if (sig == SIGINT)
	{
		setstatus(sig);
		printf("\n");
		rl_on_new_line();
	}
}
