/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:27:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 18:29:30 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getstatus(int status)
{
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		return WTERMSIG(status) + 128;
	else
		return (-1);
}

void	sighandler(int sig)
{
	int	i;

	i = -1;
	if (prog.cmdli)
	{
		while (prog.cmdli->cmds[++i])
		{
			if (!kill(prog.cmdli->cmds[i]->pid, sig) && prog.cmdli->cmds[i]->pid == prog.cmdli->lastpid)
				setstatus(sig);
		}
		printf("\n");
	}
	else if (sig == SIGINT)
	{
        printf("\n");
		rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
}
