/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:27:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 13:55:22 by fghysbre         ###   ########.fr       */
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
	if (sig == SIGQUIT)
		return ;
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
