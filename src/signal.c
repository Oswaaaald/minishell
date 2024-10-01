/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:27:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 12:53:21 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigheredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(EXIT_FAILURE);
	}
}

void	sighandler(int sig)
{
	g_prog.interupt = sig;
	if (sig == SIGINT)
	{
		if (g_prog.status == ST_IDLE)
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_prog.lastexit = 1;
		}
		else if (g_prog.status == ST_FINISH)
		{
			printf("\n");
			close(STDIN_FILENO);
		}
	}
}
