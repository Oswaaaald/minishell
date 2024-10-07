/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:42:25 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 14:35:09 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LONGSTR "mishell: syntax error near unexpected token `"

char	*getredirfromnext(t_prog *prog, t_cmd *cmd, int *i, int *j);
char	*getredirfromcurrent(t_prog *prog, t_cmd *cmd, int *i, int *j);
int		remlastmeta(t_prog *prog, t_cmd *cmd, int i);
int		strarrpop(t_prog *prog, t_cmd *cmd, int i);
