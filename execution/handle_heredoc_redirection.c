/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:42:33 by suroh             #+#    #+#             */
/*   Updated: 2025/03/15 16:18:51 by suroh            ###   ########.fr       */
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

/*
 * static int	setup_heredoc_pipe(int pipefd[2])
 * 	Purpose:
 * 		Creates a new pipe that will be used to transfer heredoc
 * 			content from the shell (after collecting it) to
 * 			the child process’s standard input.
 * 	How It Works:
 * 		pipe(pipefd):
 * 			The system call pipe() takes an array of two integers.
 * 				On success, pipefd[0] becomes the read end and
 * 				pipefd[1] the write end of the pipe.
 * 		Error Handling:
 * 			If pipe() fails (for example, due to resource limits),
 * 				perror("pipe") prints a descriptive error message,
 * 				and the function returns -1.
 *
 *
 * static int	write_heredoc_to_pipe(const char *heredoc, int pipe_out)
 *  Purpose:
 *  	Writes the collected heredoc content into the write end of the pipe.
 *  How It Works:
 *  	write(pipe_out, heredoc, ft_strlen(heredoc)):
 *  		The write() system call sends the heredoc content
 *  			(a string) to the file descriptor pipe_out.
 *  Error Handling:
 *  	If the write fails, the function returns -1; otherwise, it returns 0.
 *
 *
 * static int	redirect_pipe_to_stdin(int read_fd)
 *  Purpose:
 *  	Redirects the read end of the pipe to standard input (STDIN)
 *  		so that the command executed in the child process reads
 *  		from the heredoc content.
 *  How It Works:
 *  	dup2(read_fd, STDIN_FILENO):
 *  		Duplicates read_fd onto file descriptor 0 (STDIN).
 *  			After a successful call, STDIN now points to the pipe.
 *  	Error Handling:
 *  		If dup2() fails, it prints an error with perror("dup2"),
 *  			closes the read_fd, and returns a nonzero value.
 *  			On success, it closes the original read_fd
 *  			(because it’s now duplicated) and returns 0.
 *
 *
 * int	handle_heredoc_redirection(t_redir *redir)
 *  Purpose:
 *  	Handles a heredoc redirection by using the heredoc content
 *  		stored in the redirection node.
 *  	It creates a pipe, writes the heredoc content into the pipe,
 *  		closes the write end, and redirects STDIN to
 *  		the pipe’s read end.
 *  How It Works:
 *      Pipe Creation:
 *      	Calls setup_heredoc_pipe() to create a pipe.
 *      Write Content:
 *      	Uses write_heredoc_to_pipe() to write the heredoc content
 *      		(stored in redir->heredoc_content) into the
 *      		pipe’s write end.
 *      Close and Redirect:
 *      	Closes the write end; then calls redirect_pipe_to_stdin()
 *      		to duplicate the read end onto STDIN.
 *      Error Handling:
 *      	If any step fails, prints an error (using perror) and
 *      		returns -1.
 *
 */
