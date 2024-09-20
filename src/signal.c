/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:27:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/20 19:07:00 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	int	i;

	i = -1;
	if (g_prog.cmdli)
	{
		while (g_prog.cmdli->cmds[++i])
		{
			if (kill(g_prog.cmdli->cmds[i]->pid, sig) == -1)
				printf("mishell: failed to kill process with pid: %d\n",
					g_prog.cmdli->cmds[i]->pid);
		}
		printf("\n");
	}
	else if (sig == SIGINT)
	{
		setstatus(sig);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
