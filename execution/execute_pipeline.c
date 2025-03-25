/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:43:54 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 16:29:09 by suroh            ###   ########.fr       */
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
	mighty->exit_stat = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}
