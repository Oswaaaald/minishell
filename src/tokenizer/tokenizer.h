/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:24:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 23:32:23 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		nbcmds(char *line);
char	**arrayaddback(char **currentarr, char *str);
void	getcmds(t_cmdli *ret, char **args);
void	*freem(char **str, int a);
char	**splitline(char const *s);
int		unfinished(char *line);
int		finish(char **lineptr);
