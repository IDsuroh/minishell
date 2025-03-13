/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:13:52 by suroh             #+#    #+#             */
/*   Updated: 2025/03/13 18:26:35 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	child_exec(t_simple_cmd *cmd, t_almighty *mighty)
{
	char	*exec_path;

	if (execute_redirections(cmd->redir) < 0)
		exit(EXIT_FAILURE);
	exec_path = ft_strdup("\tNOTIMPLEMENTED\t\n");
//	exec_path = find_executable(cmd->argv[0]);
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

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		init_signals_subshell();
		child_exec(cmd, mighty);
	}
	return (parent_exec(mighty, pid));
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
