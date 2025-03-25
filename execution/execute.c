/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:13:52 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 19:45:41 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_child_command(t_simple_cmd *cmd, t_almighty *mighty)
{
	char		*exec_path;
	char		**new_envp;
	struct stat	st;

	if (execute_redirections(cmd->redir) < 0)
		exit(1);
	exec_path = find_executable(cmd->argv[0]);
	if (!exec_path || !validate_command_tokens(cmd))
		handle_cmd_not_found(cmd, mighty, exec_path);
	else if (ft_strchr(cmd->argv[0], '/') != NULL)
	{
		if (stat(exec_path, &st) != 0)
			handle_no_file_error(mighty, exec_path);
		else if (S_ISDIR(st.st_mode))
			handle_dir_error(mighty, exec_path);
	}
	else if (stat(exec_path, &st) != 0)
		handle_cmd_not_found(cmd, mighty, exec_path);
	else if (S_ISDIR(st.st_mode))
		handle_dir_error(mighty, exec_path);
	new_envp = make_envp(mighty->var_list);
	execve(exec_path, cmd->argv, new_envp);
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
	mighty->exit_stat = WEXITSTATUS(status);
	return (status);
}

static int	process_command(t_op_sequence *op, t_almighty *mighty)
{
	if (op->pipe)
	{
		if (op->pipe->next)
			return (execute_pipeline(op->pipe, mighty));
		if (is_builtin_command(op->pipe->cmd->argv[0])
			&& !op->pipe->cmd->in_pipeline)
			return (execute_builtin(op->pipe->cmd, mighty));
		return (execute_command(op->pipe->cmd, mighty));
	}
	return (0);
}

void	execute_parsed_structure(t_op_sequence *op_seq, t_almighty *mighty)
{
	t_op_sequence	*tmp_op;
	int				status;

	tmp_op = op_seq;
	while (tmp_op)
	{
		status = process_command(tmp_op, mighty);
		if (mighty->interactive)
			restore_stdin_to_tty();
		else
		{
			if (status < 256)
				exit(status);
			exit(WEXITSTATUS(status));
		}
		if ((tmp_op->op == OP_AND && status != 0)
			|| (tmp_op->op == OP_OR && status == 0))
			break ;
		tmp_op = tmp_op->next;
	}
}
