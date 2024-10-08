/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:24:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/08 16:58:24 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		nbcmds(char *line);
char	**arrayaddback(t_prog *prog, char **currentarr, char *str);
int		getcmds(t_prog *prog, t_cmdli *ret, char **args);
void	*freem(t_prog *prog, char **str, int a);
char	**splitline(t_prog *prog, char const *s);
int		remquotes(t_prog *prog, t_cmd *cmd);
char	*expander(t_prog *prog, char *str, int last, char *buff);
