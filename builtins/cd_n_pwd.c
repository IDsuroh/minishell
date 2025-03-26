/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_n_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:12:33 by suroh             #+#    #+#             */
/*   Updated: 2025/03/26 22:39:29 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_cd(t_almighty *mighty, char **args)
{
	char	*dir;
	int		alloc;

	alloc = 0;
	if (count_args(args) == 0)
		alloc = 1;
	mighty->exit_stat = 0;
	dir = resolve_dir(mighty, args);
	if (!dir)
	{
		mighty->exit_stat = 1;
		return ;
	}
	if (change_and_update_oldpwd(mighty, dir) < 0)
	{
		mighty->exit_stat = 1;
		return ;
	}
	update_new_pwd(mighty);
	if (alloc)
		free(dir);
}

void	_pwd(t_almighty *mighty)
{
	char	*buff;

	mighty->exit_stat = 0;
	buff = getcwd(NULL, 0);
	if (buff)
	{
		ft_putstr_fd(buff, 1);
		ft_putstr_fd("\n", 1);
		free(buff);
	}
	else
	{
		ft_putstr_fd("pwd:  error retrieving current directory\n",
			STDERR_FILENO);
		mighty->exit_stat = 1;
	}
}
