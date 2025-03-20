/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:13:52 by suroh             #+#    #+#             */
/*   Updated: 2025/03/20 23:07:21 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_child_command(t_simple_cmd *cmd, t_almighty *mighty)
{
	char		*exec_path;
	char		**new_envp;
	struct stat	st;

	if (execute_redirections(cmd->redir) < 0)
		exit(EXIT_FAILURE);
	exec_path = find_executable(cmd->argv[0]);
	if (!exec_path || !validate_command_tokens(cmd))
		handle_cmd_not_found(cmd, mighty, exec_path);
	if (stat(exec_path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			handle_dir_error(mighty, exec_path);
	}
	else
		handle_no_file_error(mighty, exec_path);
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

void	execute_parsed_structure(t_op_sequence *op_seq, t_almighty *mighty)
{
	t_op_sequence	*tmp_op;
	int				status;

	status = 0;
	tmp_op = op_seq;
	while (tmp_op)
	{
		if (tmp_op->pipe)
		{
			if (tmp_op->pipe->next)
				status = execute_pipeline(tmp_op->pipe, mighty);
			else
			{
				if (is_builtin_command(tmp_op->pipe->cmd->argv[0])
					&& !tmp_op->pipe->cmd->in_pipeline)
					status = execute_builtin(tmp_op->pipe->cmd, mighty);
				else
					status = execute_command(tmp_op->pipe->cmd, mighty);
			}
		}
		if ((tmp_op->op == OP_AND && status != 0)
			|| (tmp_op->op == OP_OR && status == 0))
			break ;
		tmp_op = tmp_op->next;
	}
}

/*
 * void	execute_child_command(t_simple_cmd *cmd, t_almighty *mighty)
 * Execute Redirections:
 * 	starts by execute_redirections(cmd->redir)
 * 		to set up any file redirections
 * 		(like input/output redirection or heredoc)
 * 		for the command.
 *	redirections fail, it exits immediately
 *
 * PATH Expansion:
 * 	Next, find_executable(cmd->argv[0]) is called
 * 		to resolve the full path of the command.
 * 	This function searches through the directories listed
 * 		in the PATH environment variable.
 * 	If the executable cannot be found, perror("find_executable")
 * 		is called to print an error message, and the function exits
 *
 * Generate Updated Environment:
 * 	The function calls make_envp(mighty->var_list)
 * 		to convert the internal environment representation
 * 		(var_list) into a standard char ** array.
 *	ensures that any changes made to the environment via
 *		built-in commands are passed to the external command.
 *
 * Execute the Command with execve:
 * 	The command is executed with execve(exec_path, cmd->argv, new_envp).
 *	This replaces the current process image with the new executable.
 *		If execve is successful, it never returns; if it fails,
 *		it returns, and an error message is printed with perror("execve").
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
