/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:10:10 by suroh             #+#    #+#             */
/*   Updated: 2025/03/24 15:19:51 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_pwd(t_almighty *mighty, char *buff, char *var)
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

static int	count_args(char **args)
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
	int		count;

	count = count_args(args);
	if (count > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		mighty->exit_stat = 1;
		return (NULL);
	}
	if (count == 0)
	{
		dir = getenv("HOME");
		if (!dir)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			mighty->exit_stat = 1;
			return (NULL);
		}
	}
	else
		dir = args[0];
	return (dir);
}

int	change_and_update_oldpwd(t_almighty *mighty, char *dir)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory\n", STDERR_FILENO);
		mighty->exit_stat = 1;
		return (-1);
	}
	if (chdir(dir))
	{
		ft_putstr_fd("cd:", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		mighty->exit_stat = 1;
		free(old_pwd);
		return (-1);
	}
	update_pwd(mighty, old_pwd, "OLDPWD");
	return (0);
}

void	update_new_pwd(t_almighty *mighty)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("cd: error retrieving new directory\n", STDERR_FILENO);
		mighty->exit_stat = 1;
		return ;
	}
	update_pwd(mighty, new_pwd, "PWD");
}
