/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:42:25 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 23:10:21 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LONGSTR "mishell: syntax error near unexpected token `"

char	*getredirfromnext(t_cmd *cmd, int *i, int *j);
char	*getredirfromcurrent(t_cmd *cmd, int *i, int *j);
int		remlastmeta(t_cmd *cmd, int i);
int		strarrpop(t_cmd *cmd, int i);
