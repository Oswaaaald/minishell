/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:51 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/08 23:28:39 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "unistd.h"
# include "sys/types.h"
# include "sys/wait.h"
# include "sys/stat.h"
# include "errno.h"
# include "stdio.h"
# include "string.h"
# include "stdlib.h"
# include "fcntl.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "signal.h"
# include "dirent.h"
# include "../libft/libft.h"

# define C_PIPE 1
# define C_IN 2
# define C_OUT 4

//Mini Commands
int		minicd(t_prog *prog, char **args);
int		miniecho(char **args);
int		minipwd(t_prog *prog);
int		miniexport(t_prog *prog, char **args);
int		miniunset(t_prog *prog, char **args);
int		minienv(t_prog *prog, char **args);
int		miniexit(t_prog *prog, char **args);

//Parsing

char	*ft_readline(t_prog *prog);
int		expandcmd(t_prog *prog, t_cmd *cmd);
char	*expandstr(t_prog *prog, char *str);
int		translationorwhatevahhandler(t_prog *prog,
			char **buff, char *str, int i);
char	*parsepath(t_prog *prog, char *path);
t_cmdli	*tokenize(t_prog *prog, char *line);
char	*pather(t_prog *prog, char *cmd);
int		getredirs(t_prog *prog, t_cmd *cmd);

//Checker

int		checkcmd(t_cmd *cmd);
int		checkfiles(t_cmd *cmd);
int		checksyntax(char *str);

//Signal

void	sighandler(int sig);
void	sigheredoc(int sig);

//Exec

int		cmd(t_prog *prog, t_cmdli *cmdli, int i);
int		cmdbuiltin(t_prog *prog, t_cmdli *cmdli, int i);
int		exebuiltin(t_prog *prog, t_cmd *cmd);
int		dupfds(t_cmdli *cmdli, int pfd[2], int i, int prev_fd);
int		openfd(t_prog *prog, t_cmd *cmd);
int		writeheredoc(t_prog *prog, char *lim);

//Utils

int		initprog(t_prog *prog, char **envp, int stds[2]);

/**
 * @brief Free's a 2D array's children and the array itself
 * @param arr The 2D array to free
 * @returns Nothing
 */
void	free2d(t_prog *prog, char **arr);

/**
 * @brief Returns a duplicate of a string array
 * @param arr The string array to duplicate
 * @note The array and its children are all malloc'ed
 * @returns A duplicate of the string
 */
char	**strarrdup(t_prog *prog, char **arr);

/**
 * @brief Updates or adds a environment variable to the program's array
 * @param var The string to be added or updated in env vars
 * @note Prefered string looks like: "${Name}=${Value}"
 * @retval 1 Operation successful
 * @retval 0 Operation failed
 */
int		ft_setenv(t_prog *prog, char *var);

/**
 * @brief Get's environment variable from the program's array
 * @param s The name of the env var to look for
 * @note Freeing the returned pointer is not recomended, could brake everything
 * @returns The pointer to the env variable found in programs array
 */
char	*ft_getenv(t_prog *prog, char *s);

/**
 * @brief Removes a environment variable from the program's array
 * @param s A pointer to env var found in programs array
 * @note needs the exact pointer found in programs array,
 * can be found with ft_getenv
 * @retval 1 Operation Successful
 * @retval 0 Operation failed
 */
int		ft_remenv(t_prog *prog, char *s);

/**
 * @brief Checks if string has an okay name to potentially be a
 * environment variable
 * @param s The string to be checked
 * @returns Validity of name:
 * - `1` OK
 * - `0` Not OK
 */
int		nameisvalid(char *s);

/**
 * @brief Updates the programs last status
 * @param status The value of the new status
 * @note Used to update to the exit code of the last ran program
 * @returns Nothing
 */
void	setstatus(int status);

/**
 * @brief Free's the program and all un-free'ed pointers found
 * @returns Nothing
 */
void	freeprog(t_prog *prog);

/**
 * @brief Checks if a command is a builtin command
 * @param cmdl The pointer to the cmd struct to be checked
 * @note Only Argv[0] is checked and has to be set
 * @returns if cmd is a builtin or not:
 * - `1` Is a builtin
 * - `0` Isn't a builtin
 */
int		checkbuiltin(t_cmd *cmdl);

/**
 * @brief Duplicates n bytes of a string
 * @param str The string to duplicate
 * @param n The n bytes of the string to dup
 * @note returned pointer is malloc'ed
 * @returns A pointer to the dupped str
 */
char	*ft_strndup(t_prog *prog, char *str, int n);

/**
 * @brief Duplicates a string without (omitting) len bytes from start
 * @param str The string to dup
 * @param start The start index to omit
 * @param len The number of bytes to omit
 * @returns A pointer to the new str
 * @note Example: `stromit("heyomitwhy", 3, 4)` => `"heywhy"`
 */
char	*stromit(t_prog *prog, char *str, int start, int len);

/**
 * @brief Closes two fd's of a int[2]
 * @param fd The int[2] to be closed
 * @returns Nothing
 * @note No checks are made, just saves a line.
 */
void	closefd(int fd[2]);

/**
 * @brief Join's two strings while adding a character in between
 * @param s1 The first string to be joined
 * @param s2 The second string to be joined
 * @param fil The character to be added in between both strings
 * @returns A pointer to the new combined string
 * @note returned pointer is malloc'ed
 */
char	*strcjoin(t_prog *prog, char *s1, char *s2, char fil);

/**
 * @brief Tranforms a string array into a linked list
 * @param s1 The string array to be transformed
 * @returns A pointer to the first element of the new linked list
 */
t_list	*arrtolst(t_prog *prog, char **arr);

/**
 * @brief Join's a linked list into a string array
 * @param lst The first node of the linked list to be joined
 * @returns A pointer to joined string
 * @note returned pointer is malloc'ed
 */
char	*lstjoin(t_prog *prog, t_list *lst);

/**
 * @brief Check's if a string points to a directory
 * @param path The path string to the supposed directory
 * @returns if path is a Directory or not:
 * - `1` Is a Directory
 * - `0` Isn't a Directory
 */
int		isdir(char *path);

/**
 * @brief Free's a cmdli and its member nodes
 * @param cmdli The cmdli to free
 * @returns Nothing
 */
void	freecmdli(t_prog *prog, t_cmdli *cmdli);

void	exportputerror(int cmd, int type, char c, char *s);

int		checkerputerror(int type, char *s, int ret);

void	setbrutestatus(int stat);

int		getendofvar(char *str, int i, int si);

void	updatequotes(int quotes[2], char c);

void	updatestr(t_prog *prog, int *status, char **str, char *new);

int		exportspecialcase(t_prog *prog, char *str);

#endif