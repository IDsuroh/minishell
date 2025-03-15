/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:13:52 by suroh             #+#    #+#             */
/*   Updated: 2025/03/15 20:11:01 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_child_command(t_simple_cmd *cmd, t_almighty *mighty)
{
	char	*exec_path;

	if (execute_redirections(cmd->redir) < 0)
		exit(EXIT_FAILURE);
	exec_path = find_executable(cmd->argv[0]);
	if (!exec_path)
	{
		perror("find_executable");
		exit(EXIT_FAILURE);
	}
	execve(exec_path, cmd->argv, mighty->envp);
	perror("execve");
	free(exec_path);
	exit(EXIT_FAILURE);
}

static int	parent_exec(t_almighty *mighty, pid_t pid)
{
	int	status;

	add_child_pid(mighty, pid);
	waitpid(pid, &status, 0);
	remove_child_pid(mighty, pid);
	return (status);
}

int	execute_command(t_simple_cmd *cmd, t_almighty *mighty)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		init_signals_subshell();
		execute_child_command(cmd, mighty);
	}
	status = parent_exec(mighty, pid);
	return (status);
}

void	execute_parsed_structure(t_op_sequence *op_seq, t_almighty *mighty)
{
	t_op_sequence	*tmp_op;
	int				status;

	status = 0;
	tmp_op = op_seq;
	while (tmp_op)
	{
		if (tmp_op->pipe && tmp_op->pipe->next)
			status = execute_pipeline(tmp_op->pipe, mighty);
		else if (tmp_op->pipe)
			status = execute_command(tmp_op->pipe->cmd, mighty);
		if (tmp_op->op == OP_AND && status != 0)
			break ;
		if (tmp_op->op == OP_OR && status == 0)
			break ;
		tmp_op = tmp_op->next;
	}
}

/*
 * static void	child_exec(t_simple_cmd *cmd, t_almighty *mighty)
 * 	Calls execute_redirections to set up any file redirections.
 * 	Uses a placeholder for PATH expansion
 * 		(to be replaced with find_executable later).
 * 	Calls execve with the command’s arguments and the environment
 * 		stored in mighty.
 * 	If any error occurs, it prints an error (via perror) and
 * 		exits with EXIT_FAILURE.
 *
 * 
 * static int	parent_exec(t_almighty *mighty, pid_t pid)
 *  Tracks the child process for later signal forwarding.
 *  Uses waitpid to block until the child completes.
 *  Removes the child’s PID from the active list.
 *  Returns the child's exit status.
 *
 *
 * int	execute_command(t_simple_cmd *cmd, t_almighty *mighty)
 *  Forks a child process.
 *  In the child branch, resets signal handlers to default
 *  	(via init_signals_subshell) and calls child_exec.
 *  In the parent branch, waits for the child and
 *  	returns its exit status.
 *
 *
 * void	execute_parsed_structure(t_op_sequence *op_seq, t_almighty *mighty)
 *  Iterates through each command group (op_sequence).
 *  If there is more than one command in the pipeline, calls
 *  	execute_pipeline; otherwise, calls execute_command.
 *  Checks the logical operator (OP_AND or OP_OR) to decide whether to
 *  	continue executing subsequent command groups.
 *
 */
