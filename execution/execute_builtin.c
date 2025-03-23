/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:35:16 by suroh             #+#    #+#             */
/*   Updated: 2025/03/23 22:18:59 by suroh            ###   ########.fr       */
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

static int	apply_builtin_redir(t_simple_cmd *cmd)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
	{
		perror("dup");
		return (-1);
	}
	if (execute_redirections(cmd->redir) < 0)
		return (-1);
	return (saved_stdout);
}

static void	dispatch_builtin(t_simple_cmd *cmd, t_almighty *mighty,
			int saved_stdout)
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
	{
		close(saved_stdout);
		_exit_(mighty, NULL);
	}
}

int	execute_builtin(t_simple_cmd *cmd, t_almighty *mighty)
{
	int	saved_stdout;
	int	status;

	saved_stdout = apply_builtin_redir(cmd);
	if (saved_stdout < 0)
		return (-1);
	dispatch_builtin(cmd, mighty, saved_stdout);
	status = mighty->exit_stat;
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		perror("dup2");
	close(saved_stdout);
	return (status);
}

/*
 * bool	is_builtin_command(const char *cmd)
 *  This function checks if a given command name (passed as cmd)
 *  	is one of the built-in commands that the shell must handle
 *  	internally.
 *
 *
 * int	execute_builtin(t_simple_cmd *cmd, t_almighty *mighty)
 *  This function dispatches the execution of a built-in command
 *  	based on the command name found in cmd->argv[0].

 *
 */
