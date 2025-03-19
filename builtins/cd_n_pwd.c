/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_n_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:12:33 by suroh             #+#    #+#             */
/*   Updated: 2025/03/19 17:53:29 by suroh            ###   ########.fr       */
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

void	_cd(t_almighty *mighty, char *dir)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, 0);
	if (chdir(dir))
	{
		ft_putstr_fd("cd:", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	update_pwd(mighty, buff, "OLDPWD");
	buff = getcwd(buff, 0);
	update_pwd(mighty, buff, "PWD");
}

void	_pwd(void)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, 0);
	if (buff)
	{
		ft_putstr_fd(buff, 1);
		ft_putstr_fd("\n", 1);
	}
	free(buff);
}
