/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:27:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/23 16:01:02 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	int	i;

	i = -1;
	g_prog.interupt = 1;
	close(STDIN_FILENO);
	if (g_prog.cmdli)
	{
		while (g_prog.cmdli->cmds[++i])
		{
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
