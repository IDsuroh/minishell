/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:03:54 by suroh             #+#    #+#             */
/*   Updated: 2025/03/19 17:21:51 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_echo(char **args)
{
	bool	dash_n;

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

/*
 * echo:
 * Consume "-n" Flags:
 * The loop checks if the current argument is exactly "-n" using ft_strcmp.
 * For each "-n", it sets dash_n to true and advances the args pointer.
 *
 * Printing Arguments:
 * The next loop prints each remaining argument. If there’s another argument
 * following the current one, it prints a space in between.
 *
 * Newline Control:
 * Finally, if no "-n" flag was found, a newline is printed.
 */
