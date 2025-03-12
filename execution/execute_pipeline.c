/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:43:54 by suroh             #+#    #+#             */
/*   Updated: 2025/03/12 16:04:33 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	fork_pipeline(t_pipe_sequence *current,
		int	*prev_pipe_read, t_almighty *mighty, int pipefd[2])
{
	t_pipeline_variables	pvs;	
	pid_t					pid;

	pvs.current = current;
	pvs.prev_pipe_read = *prev_pipe_read;
	pvs.pipefd[0] = pipefd[0];
	pvs.pipefd[1] = pipefd[1];
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_pipeline_setup(&pvs, mighty);
	else
	{
		parent_pipeline_setup(&pvs, mighty, pid);
		*prev_pipe_read = pvs.prev_pipe_read;
	}
}

static void	process_pipeline(t_pipe_sequence *current,
		int *prev_pipe_read, t_almighty *mighty)
{
	int	pipefd[2];

	if (current->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pipefd[0] = -1;
		pipefd[0] = -1;
	}
	fork_pipeline(current, prev_pipe_read, mighty, pipefd);
}

int	execute_pipeline(t_pipe_sequence *pipe_seq, t_almighty *mighty)
{
	int				prev_pipe_read;
	int				status;
	t_pipe_sequence	*pipe_point;

	prev_pipe_read = -1;
	pipe_point = pipe_seq;
	while (pipe_point)
	{
		process_pipeline(pipe_point, &prev_pipe_read, mighty);
		pipe_point = pipe_point->next;
	}
	while (wait(&status) > 0)
		;
	return (status);
}

/*
 * static void	fork_pipeline:
 *	t_pipeline_variables: groups current pipeline node, previous
 *	pipe's read end, and current pipe descriptors.
 *	Forking: In the child, call child_pipeline_setup.
 *			In the parent, call parent_pipeline_setup and update
 *			prev_pipe_read.
 *
 *
 * static void	process_pipeline:
 * 	pipe(): if there is another command, a new pipe is created.
 * 			if not, pipe file descriptors are set to -1.
 *	Then call fork_pipeline().
 *
 *
 * int	execute_pipeline:
 * 	This function loops through each pipeline segment and waits
 * 	for all the children to finish.
 * 	Waiting: After all segments are launched, meaning that once the
 * 			pipeline code has finished creating (forking) all the
 * 			child processes for each command in the pipeline,
 * 			the parent process then enters a waiting phase.
 *	Then returns a status which is important for '||' and '&&'
 *
 * For pipelines, multiple child processes are created thus should be
 * connected through STDOUT and STDIN.
 *
 *
 *
 */
