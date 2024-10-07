/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:55:18 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 14:47:00 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freeprog(t_prog *prog)
{
	t_list	*tmp;
	t_list	*crnt;

	crnt = prog->mallocs;
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

void	freecmdli(t_prog *prog, t_cmdli *cmdli)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	while (++i < cmdli->nbcmds)
	{
		cmd = cmdli->cmds[i];
		if (cmd->argv)
			free2d(prog, cmd->argv);
		if (cmd->input)
			ft_free(prog, cmd->input);
		if (cmd->output)
			ft_free(prog, cmd->output);
		if (cmd->limmiter)
			ft_free(prog, cmd->limmiter);
		if (cmd->path)
			ft_free(prog, cmd->path);
		ft_free(prog, cmd);
	}
	ft_free(prog, cmdli->cmds);
	ft_free(prog, cmdli);
	prog->cmdli = NULL;
}

void	closefd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
