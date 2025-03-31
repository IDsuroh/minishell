/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:26:26 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 13:35:15 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*retrieve_old_pwd(t_almighty *mighty)
{
	char		*old_pwd;
	t_var_elm	*elm;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		elm = get_value(mighty->var_list, "PWD");
		if (elm && elm->value)
			old_pwd = ft_strdup(elm->value);
		else
		{
			ft_putstr_fd("cd: error retrieving current directory\n",
				STDERR_FILENO);
			return (NULL);
		}
	}
	return (old_pwd);
}

int	change_and_update_oldpwd(t_almighty *mighty, char *dir)
{
	char	*old_pwd;

	old_pwd = retrieve_old_pwd(mighty);
	if (!old_pwd)
	{
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
	char		*new_pwd;
	t_var_elm	*elm;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		elm = get_value(mighty->var_list, "PWD");
		if (elm && elm->value)
			new_pwd = ft_strdup(elm->value);
		else
		{
			ft_putstr_fd("cd: error retrieving new directory\n", STDERR_FILENO);
			mighty->exit_stat = 1;
			return ;
		}
	}
	update_pwd(mighty, new_pwd, "PWD");
}
