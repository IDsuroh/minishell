/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:57:10 by suroh             #+#    #+#             */
/*   Updated: 2025/03/13 18:18:52 by suroh            ###   ########.fr       */
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

static void	execute_child(t_pipeline_variables *pvs)
{
	if (execute_redirections(pvs->current->cmd->redir) < 0)
		exit(EXIT_FAILURE);
	// $PATH expansion
	// execve
}

void	child_pipeline_setup(t_pipeline_variables *pvs, t_almighty *mighty)
{
	(void)mighty;
	init_signals_subshell();
	child_redirect_stdio(pvs);
	child_close_fds(pvs);
	execute_child(pvs);
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
