/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:10:10 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 13:35:00 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_pwd(t_almighty *mighty, char *buff, char *var)
{
	t_var_elm	*elm;

	elm = get_value(mighty->var_list, var);
	if (elm)
	{
		free(elm->value);
		elm->value = ft_strdup(buff);
	}
	else
		add_var(mighty->var_list, create_var(ft_strdup(var),
				ft_strdup(buff)));
	free(buff);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

char	*resolve_dir(t_almighty *mighty, char **args)
{
	char	*dir;
	char	*home;
	int		count;

	count = count_args(args);
	if (count > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		mighty->exit_stat = 1;
		return (NULL);
	}
	if (count == 0 || (count == 1 && ft_strcmp(args[0], "~") == 0))
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			mighty->exit_stat = 1;
			return (NULL);
		}
		dir = ft_strdup(home);
	}
	else
		dir = args[0];
	return (dir);
}
