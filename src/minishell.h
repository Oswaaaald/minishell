/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:51 by codespace         #+#    #+#             */
/*   Updated: 2024/07/17 10:58:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define C_PIPE 1
#define C_IN 2
#define C_OUT 4

//A command that is in a promt line
typedef struct s_cmd {
    char    *path;
    char    **argv;
    char    **env;
    char    *input;
    char    *output;
    char    *limmiter;
    int     outappend;
}   t_cmd;

//All the commabds in the command primt plus extra data
typedef struct s_cmdli {
    t_cmd   **cmds;
    pid_t   lastPid;
}   t_cmdli;

//The data that is used to run the shell
typedef struct s_prog {
    char    lastExit;
    char    cwd[256];
}   t_prog;
