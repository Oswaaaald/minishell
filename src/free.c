/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:55:18 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/02 00:42:38 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freeprog(void)
{
	t_list	*tmp;
	t_list	*crnt;

	crnt = g_prog.mallocs;
	while (crnt)
	{
		tmp = crnt->next;
		if (crnt->content)
			free(crnt->content);
		free(crnt);
		crnt = tmp;
	}
	rl_clear_history();
}

void	freecmdli(t_cmdli *cmdli)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	while (++i < cmdli->nbcmds)
	{
		cmd = cmdli->cmds[i];
		if (cmd->argv)
			free2d(cmd->argv);
		if (cmd->input)
			ft_free(cmd->input);
		if (cmd->output)
			ft_free(cmd->output);
		if (cmd->limmiter)
			ft_free(cmd->limmiter);
		if (cmd->path)
			ft_free(cmd->path);
		ft_free(cmd);
	}
	ft_free(cmdli->cmds);
	ft_free(cmdli);
	g_prog.cmdli = NULL;
}

void	closefd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
