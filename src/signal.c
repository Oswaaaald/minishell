/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:27:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/18 16:37:13 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	int	i;

	i = -1;
	if (prog.cmdli)
	{
		while (prog.cmdli->cmds[++i])
		{
			if (!kill(prog.cmdli->cmds[i]->pid, sig) && prog.cmdli->cmds[i]->pid == prog.cmdli->lastpid)
				//setstatus(sig);
				;
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
