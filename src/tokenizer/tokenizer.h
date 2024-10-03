/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:24:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 13:20:36 by fghysbre         ###   ########.fr       */
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
int		remquotes(t_cmd *cmd);
