/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:09 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/02 17:06:59 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**strarrsort(char **arr)
{
	int		i;
	char	*temp;

	i = 0;
	while (arr[++i])
	{
		if (ft_strncmp(arr[i], arr[i - 1], -1) < 0)
		{
			temp = arr[i];
			arr[i] = arr[i - 1];
			arr[i - 1] = temp;
			i = i - 2;
		}
		if (i < 0)
			i = 0;
	}
	return (arr);
}

void	putdeclare(char *s)
{
	int	i;
	int	togg;

	i = -1;
	togg = 0;
	write(STDOUT_FILENO, "declare -x ", 11);
	while (s[++i])
	{
		write(STDOUT_FILENO, &s[i], 1);
		if (s[i] == '=' && !togg)
		{
			write(STDOUT_FILENO, "\"", 1);
			togg = 1;
		}
	}
	if (togg)
		write(STDOUT_FILENO, "\"", 1);
	write(STDOUT_FILENO, "\n", 1);
}

void	expshowall(void)
{
	int		i;
	char	**envdup;

	i = -1;
	envdup = strarrdup(g_prog.minienv);
	if (!envdup)
		return ;
	envdup = strarrsort(envdup);
	while (envdup[++i])
		putdeclare(envdup[i]);
}

int	nameisvalid(char *s)
{
	int	i;
	int	togg;

	togg = 0;
	i = -1;
	while (s[++i])
	{
		if (i == 0 && s[i] == '=')
			return (0);
		if (s[i] == '=')
			togg = 1;
		if (i == 0 && !(ft_isalpha(s[i]) || s[i] == '_') && !togg)
			return (0);
		else if (i > 0 && !(ft_isalnum(s[i]) || s[i] == '_') && !togg)
			return (0);
	}
	return (1);
}

int	miniexport(char **args)
{
	int	i;
	int	togg;

	if (!args[1])
		return (expshowall(), 0);
	i = 0;
	togg = 0;
	while (args[++i])
	{
		if (i == 1 && !ft_strncmp(args[i], "--", -1))
			i++;
		if (i == 1 && args[i][0] == '-')
			return (printf("mishell: export: -%c: invalid option\n",
					args[i][1]), 2);
		else if (!nameisvalid(args[i]))
			printf("mishell: export: %s: not a valid indetifier\n", args[i]);
		else
		{
			if (!ft_setenv(ft_strdup(args[i])))
				printf("Warning: A malloc has failed");
			continue ;
		}
		togg = 1;
	}
	return (togg);
}
