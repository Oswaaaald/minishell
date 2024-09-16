/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:51 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 18:04:03 by fghysbre         ###   ########.fr       */
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

//Mini Commands
int		minicd(char **args);
int		miniecho(char **args);
int		minipwd(void);
int		miniexport(char **args);
int		miniunset(char **args);
int		minienv(char **args);

//Parsing
char	*parsepath(char *path);
t_cmdli	*tokenize(char *line);

//Signal
void	sighandler(int sig);

//Utils
int		initprog(char **envp);
void	free2d(char **arr);
char	**strarrdup(char **arr);
int		ft_setenv(char *var);
char	*ft_getenv(char *s);
int		ft_remenv(char *s);
int		nameisvalid(char *s);
void	setstatus(int status);

#endif