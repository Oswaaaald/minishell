

int	cmd(t_cmdli *cmdli, int i, int prev_fd)
{
	pid_t		pid;
	t_cmd		*cmd;

	cmd = cmdli->cmds[i];
	pid = fork();
	if (!pid)
	{
		if (cmdli->cmds[i + 1] || cmd->output)
			dup2(cmd->fd[1], STDOUT_FILENO);
		if (prev_fd && (i || cmd->input || cmd->limmiter))
			dup2(prev_fd, STDIN_FILENO);
		closefd(cmd->fd);
		if (!checkbuiltin(cmd))
		{
			if (execve(cmd->path, cmd->argv, g_prog.minienv))
				exit(EXIT_FAILURE);
		}
		else
			exit(exebuiltin(cmd));
	}
	if (!cmdli->cmds[i + 1] && pid > 0)
		cmdli->lastpid = pid;
	cmd->pid = pid;
	close(cmd->fd[1]);
	return (1);
}

while (++i < g_prog.cmdli->nbcmds)
{
	pipe(g_prog.cmdli->cmds[i].fd)
}
i = 0;
int	prev_fd;
prev_fd = 0;
while (i < g_prog.cmdli->nbcmds)
{
		if (i == 0)
			prev_fd = g_prog.cmdli->cmds[0]->fd[0];
		if (!cmd(g_prog.cmdli, i, prev_fd))
			return (0);
		if (i != 0)
			close(prev_fd);
		prev_fd = g_prog.cmdli->cmds[i]->fd[0];
}
