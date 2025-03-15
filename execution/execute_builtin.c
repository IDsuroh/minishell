/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:35:16 by suroh             #+#    #+#             */
/*   Updated: 2025/03/15 20:37:37 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_builtin_command(const char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(t_simple_cmd *cmd, t_almighty *mighty)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		_echo(cmd->argv + 1);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		_cd(mighty, cmd->argv[1]);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		_pwd();
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		_export(mighty, cmd->argv[1]);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		_unset(mighty, cmd->argv[1]);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		_env(mighty);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		_exit_(mighty, NULL);
	return (0);
}
