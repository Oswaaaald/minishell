/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:51 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/13 17:28:03 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "errno.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "fcntl.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "signal.h"
#include "dirent.h"
#include "../libft/libft.h"

#define C_PIPE 1
#define C_IN 2
#define C_OUT 4

extern char	**environ;

//A command that is in a promt line
typedef struct s_cmd
{
	char	*path;
	char	**argv;
	char	**env;
	char	*input;
	char	*output;
	char	*limmiter;
	int		outappend;
}	t_cmd;

//All the commabds in the command primt plus extra data
typedef struct s_cmdli
{
	t_cmd	**cmds;
	int		nbcmds;
	pid_t	lastpid;
}	t_cmdli;

//Mini Commands
int		minicd(t_prog *prog, char **args);
int		miniecho(char **args);
int		minipwd(t_prog *prog);
int		miniexport(t_prog *prog, char **args);
int		miniunset(t_prog *prog, char **args);
int		minienv(t_prog *prog, char **args);

//Parsing
char	*parsepath(t_prog *prog, char *path);
t_cmdli	*tokenize(t_prog *prog, char *line);

//Utils
int		initprog(t_prog *prog, char **envp);
void	free2d(t_prog *prog, char **arr);
char	**strarrdup(t_prog *prog, char **arr);
int		ft_setenv(t_prog *prog, char *var);
char	*ft_getenv(t_prog *prog, char *s);
int		ft_remenv(t_prog *prog, char *s);
int		nameisvalid(char *s);

#endif