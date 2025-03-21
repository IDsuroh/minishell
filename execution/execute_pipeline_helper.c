/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:57:10 by suroh             #+#    #+#             */
/*   Updated: 2025/03/16 15:38:56 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	child_redirect_stdio(t_pipeline_variables *pvs)
{
	if (pvs->prev_pipe_read != -1)
	{
		if (dup2(pvs->prev_pipe_read, STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (pvs->current->next)
	{
		if (dup2(pvs->pipefd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

static void	child_close_fds(t_pipeline_variables *pvs)
{
	if (pvs->prev_pipe_read != -1)
		close(pvs->prev_pipe_read);
	if (pvs->current->next)
	{
		close(pvs->pipefd[0]);
		close(pvs->pipefd[1]);
	}
}

static void	execute_child(t_pipeline_variables *pvs, t_almighty *mighty)
{
	execute_child_command(pvs->current->cmd, mighty);
}

void	child_pipeline_setup(t_pipeline_variables *pvs, t_almighty *mighty)
{
	init_signals_subshell();
	child_redirect_stdio(pvs);
	child_close_fds(pvs);
	execute_child(pvs, mighty);
}

void	parent_pipeline_setup(t_pipeline_variables *pvs,
		t_almighty *mighty, pid_t pid)
{
	add_child_pid(mighty, pid);
	if (pvs->prev_pipe_read != -1)
		close(pvs->prev_pipe_read);
	if (pvs->current->next)
	{
		close(pvs->pipefd[1]);
		pvs->prev_pipe_read = pvs->pipefd[0];
	}
}

/*
 * static void	child_redirect_stdio(t_pipeline_variables *pvs)
 *	Redirection for STDIN:
 *		If pvs->prev_pipe_read is not -1, it means that there
 *			is a previous pipe from which the current command
 *			should receive its input.
 *		dup2(pvs->prev_pipe_read, STDIN_FILENO) duplicates
 *			that file descriptor so that the standard input
 *			(file descriptor 0) now reads from the previous pipe.
 *		If dup2 fails, an error is printed with perror,
 *			and the child exits with EXIT_FAILURE.
 *	Redirection for STDOUT:
 *		If there is a next command (pvs->current->next is not NULL),
 *			it means that the current command’s output should be
 *			piped to the next command.
 *		dup2(pvs->pipefd[1], STDOUT_FILENO) duplicates the write
 *			end of the current pipe so that the standard output
 *			(file descriptor 1) now writes into the pipe.
 *		Again, failure in dup2 prints an error and exits the child.
 *
 *
 * static void	child_close_fds(t_pipeline_variables *pvs)
 *	Closing Unneeded Descriptors:
 *		Once the file descriptors are duplicated (using dup2),
 *			the original descriptors are no longer needed.
 *		If a previous pipe was used (prev_pipe_read not -1),
 *			it is closed.
 *		For commands that are not the last in the pipeline
 *			(pvs->current->next exists), both ends of the
 *			current pipe (pipefd[0] and pipefd[1]) are closed
 *			in the child process. This prevents resource leaks
 *			and ensures that the pipe behaves correctly.
 *
 *
 * static void	execute_child(t_pipeline_variables *pvs)
 *	 a simple wrapper that calls the common child command
 *	 execution routine for the current command in the pipeline.
 *
 * void	child_pipeline_setup(t_pipeline_variables *pvs, t_almighty *mighty)
 *	Signal Handling in Child:
 *		Calls init_signals_subshell() to restore default
 *			signal behavior in the child. This ensures that,
 *			for example, SIGINT (Ctrl+C) will cause the child process
 *			to terminate normally.
 *	I/O Redirection:
 *		child_redirect_stdio(pvs) sets up STDIN and STDOUT according to
 *			the pipeline needs.
 *		child_close_fds(pvs) then closes the now-unneeded file descriptors.
 *	Execute the Command:
 *		Finally, execute_child(pvs) applies any further redirections
 *			(like file redirections) and eventually executes
 *			the command via execve.
 *
 *
 * void	parent_pipeline_setup(t_pipeline_variables *pvs,
 * 		t_almighty *mighty, pid_t pid)
 *	Tracking the Child:
 *		add_child_pid(mighty, pid) adds the newly forked child's PID
 *			to a list for future signal management.
 *	Cleanup of File Descriptors:
 *		If there is a previous pipe read descriptor
 *			(prev_pipe_read is not -1), it is closed since it’s
 *			no longer needed by the parent.
 *	Prepare for Next Pipeline Segment:
 *		If there is a next command in the pipeline
 *			(pvs->current->next exists), then the write end of
 *			the current pipe (pipefd[1]) is closed (in the parent),
 *			and the read end (pipefd[0]) is saved in pvs->prev_pipe_read
 *			to be used as STDIN for the next command.
 */
