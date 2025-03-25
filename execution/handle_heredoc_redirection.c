/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:42:33 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 16:29:43 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	setup_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

static int	write_heredoc_to_pipe(const char *heredoc, int pipe_out)
{
	if (write(pipe_out, heredoc, ft_strlen(heredoc)) < 0)
		return (-1);
	return (0);
}

static int	redirect_pipe_to_stdin(int read_fd)
{
	if (dup2(read_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(read_fd);
		return (read_fd);
	}
	close(read_fd);
	return (0);
}

int	handle_heredoc_redirection(t_redir *redir)
{
	int		pipefd[2];

	if (setup_heredoc_pipe(pipefd) > 0)
		return (-1);
	if (write_heredoc_to_pipe(redir->heredoc_content, pipefd[1]) < 0)
	{
		perror("write");
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	close(pipefd[1]);
	if (redirect_pipe_to_stdin(pipefd[0]) < 0)
		return (-1);
	return (0);
}
