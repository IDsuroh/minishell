/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:30:59 by suroh             #+#    #+#             */
/*   Updated: 2025/03/24 15:46:58 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_numeric(char *str)
{
	if (!str || !*str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	handle_no_arg_exit(t_almighty *mighty, int saved_stdout)
{
	close(saved_stdout);
	_exit_(mighty, NULL);
}

void	handle_non_numeric_exit(t_almighty *mighty, int saved_stdout)
{
	int	code;

	ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
	close(saved_stdout);
	{
		code = 2;
		_exit_(mighty, &code);
	}
}

void	handle_numeric_exit(t_almighty *mighty, char **argv, int saved_stdout)
{
	int	num;
	int	exit_val;

	num = ft_atoi(argv[1]);
	exit_val = ((num % 256) + 256) % 256;
	close(saved_stdout);
	_exit_(mighty, &exit_val);
}
