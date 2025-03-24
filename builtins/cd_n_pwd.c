/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_n_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:12:33 by suroh             #+#    #+#             */
/*   Updated: 2025/03/24 15:11:20 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_cd(t_almighty *mighty, char **args)
{
	char	*dir;

	dir = resolve_dir(mighty, args);
	if (!dir)
		return ;
	if (change_and_update_oldpwd(mighty, dir) < 0)
		return ;
	update_new_pwd(mighty);
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
	else
		ft_putstr_fd("pwd:  error retrieving current directory\n",
			STDERR_FILENO);
	free(buff);
}
