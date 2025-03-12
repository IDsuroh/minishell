/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:13:52 by suroh             #+#    #+#             */
/*   Updated: 2025/03/12 15:51:43 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (execute_redirections(cmd->redir, mighty) < 0)
			exit(EXIT_FAILURE);
		//PATH expansion should be performed here.
		//execve()
	}
	else
	{
		add_child_pid(mighty, pid);
		waitpid(pid, &status, 0);
		remove_child_pid(mighty, pid);
		return (status);
	}
	return (0);
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
 * int	execute_command(t_simple_cmd *cmd, t_almighty *mighty)
 *
 * Forking the Process:
 * 	pid = fork();
 * 		creates a new child process which the fork of the child return 0,
 * 		and the parent returns the child's PID.
 * Applies file redirections
 * then PATH expansions.
 *
 * In the Parent Process, it adds the PID of so that if a signal is received,
 * it can be forwarded.
 * Parent wairs for the child to finish then retrieves the exit status of it.
 * Then remove the finish child from the tracking list.
 *
 * execute_parsed_structure(t_op_sequence *op_seq, t_almighty *mighty)
 * execute commands that may be simple or complex.
 *
 *
 */
