/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:10:17 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/24 16:04:24 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_builtin(t_almighty *mighty, char **argv, int saved_stdout)
{
	if (!argv[1])
		handle_no_arg_exit(mighty, saved_stdout);
	else if (!is_numeric(argv[1]))
		handle_non_numeric_exit(mighty, saved_stdout);
	else if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		mighty->exit_stat = 1;
		if (dup2(saved_stdout, STDOUT_FILENO) < 0)
			perror("dup2");
		close(saved_stdout);
		return (1);
	}
	else
		handle_numeric_exit(mighty, argv, saved_stdout);
	return (0);
}

void	_exit_(t_almighty *mighty, int *var_exit)
{
	int	exit_val;

	if (var_exit)
		exit_val = *var_exit;
	else
		exit_val = mighty->exit_stat;
	free_all(mighty);
	exit(exit_val);
}
