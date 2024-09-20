/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boyflo06 <boyflo06@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:27:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/20 13:42:26 by boyflo06         ###   ########.fr       */
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
			if (kill(prog.cmdli->cmds[i]->pid, sig) == -1)
				printf("mishell: failed to kill process with pid: %d\n", prog.cmdli->cmds[i]->pid);
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
