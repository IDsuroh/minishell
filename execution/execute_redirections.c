/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:04:19 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 20:56:43 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*static void	print_redirection_error(const char *filename)
{
	if (errno == EACCES)
	{
		write(STDERR_FILENO, filename, ft_strlen(filename));
		write(STDERR_FILENO, ": Permission denied\n", 21);
	}
	else if (errno == ENOENT)
	{
		write(STDERR_FILENO, filename, ft_strlen(filename));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
	}
	else
		perror(filename);
}*/

static int	handle_input_redirection(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_output_redirection(const char *filename)
{
	int		fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_append_redirection(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	execute_redirections(t_redir *redir)
{
	while (redir)
	{
		if ((redir->type == T_LESS
				&& handle_input_redirection(redir->filename) < 0)
			|| (redir->type == T_GREAT
				&& handle_output_redirection(redir->filename) < 0)
			|| (redir->type == T_DGREAT
				&& handle_append_redirection(redir->filename) < 0)
			|| (redir->type == T_DLESS
				&& handle_heredoc_redirection(redir) < 0))
			return (-1);
		redir = redir->next;
	}
	return (0);
}
