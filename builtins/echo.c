/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:03:54 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 18:29:49 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_echo(t_almighty *mighty, char **args)
{
	bool	dash_n;

	mighty->exit_stat = 0;
	dash_n = false;
	while (*args && ft_strcmp(*args, "-n") == 0)
	{
		dash_n = true;
		++args;
	}
	while (*args)
	{
		ft_putstr_fd(*(args++), 1);
		if (*args)
			ft_putchar_fd(' ', 1);
	}
	if (!dash_n)
		ft_putchar_fd('\n', 1);
}
