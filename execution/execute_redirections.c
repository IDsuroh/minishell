/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:04:19 by suroh             #+#    #+#             */
/*   Updated: 2025/03/15 16:13:49 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	int	fd;

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

/*
 * static int	handle_input_redirection(const char *filename)
 * 	Purpose:
 * 		This function redirects the standard input (STDIN) from a file.
 * 		It’s used when a command uses < filename for input redirection.
 * 	Steps:
 * 		Open the File:
 *       	fd = open(filename, O_RDONLY);
 *       	Opens the file in read-only mode.
 *       	If the file cannot be opened
 *       		(e.g., it does not exist or lack permission),
 *       		open() returns -1.
 *  Error Check:
 *  	if (fd < 0) uses perror(filename) to print an error message
 *  		that includes the filename, then returns -1.
 *  Duplicate File Descriptor:
 *  	dup2(fd, STDIN_FILENO) duplicates the file descriptor fd
 *  		onto STDIN (which is file descriptor 0).
 *  	This means that after this call, any read operation from
 *  		STDIN will read from the file.
 *  	If dup2 fails, an error is printed and the file descriptor
 *  		is closed before returning -1.
 *  Close Original FD:
 *  	After duplication, the original file descriptor is no longer
 *  		needed, so it is closed.
 *  Return Success:
 *  	If everything succeeds, the function returns 0.
 *
 *
 * static int	handle_output_redirection(const char *filename)
 * 	Purpose:
 * 		This function redirects the standard output (STDOUT)
 * 			to a file. It is used when a command uses > filename
 * 			to redirect output.
 * 	Steps:
 * 		Open or Create the File:
 * 			fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
 * 			Opens the file in write-only mode; if it doesn’t exist,
 * 			it creates it with permissions 0644; if it does exist,
 * 			it truncates (empties) it.
 * 	Error Check:
 * 		If opening fails, it prints an error message
 * 			(including the filename) and returns -1.
 * 	Duplicate File Descriptor:
 * 		dup2(fd, STDOUT_FILENO) duplicates the file descriptor
 * 			onto STDOUT (file descriptor 1), so that any write
 * 			to STDOUT writes to the file.
 * 	Close Original FD:
 * 		Closes the original file descriptor after duplication.
 * 	Return Success:
 * 		Returns 0 if everything succeeded.
 *
 *
 * static int	handle_append_redirection(const char *filename)
 * 	Purpose:
 * 		This function handles output redirection in append mode
 * 			(using >> filename), so that output is appended to
 * 			the file instead of truncating it.
 * 	Steps:
 * 		Open or Create the File in Append Mode:
 * 			fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
 * 			Opens the file for writing and appends data at the end.
 * 			If the file doesn’t exist, it is created.
 * 	Error Check:
 * 		If opening fails, an error message is printed,
 * 			and the function returns -1.
 * 	Duplicate FD onto STDOUT:
 * 		dup2(fd, STDOUT_FILENO) redirects STDOUT to write to this file.
 * 	Close Original FD:
 * 		Closes the original file descriptor.
 * 	Return Success:
 * 		Returns 0 on success.
 *
 *
 * int	execute_redirections(t_redir *redir)
 *  Purpose:
 *  	This function loops through the linked list of redirection
 *  		nodes associated with a command and executes the
 *  		appropriate redirection for each.
 *  How it Works:
 *		Loop Through Redirections:
 *			It iterates through each node in the redirection list
 *				(while (redir)).
 *		Switch Based on Redirection Type:
 *			For each node, it checks the type:
 *				If the type is T_LESS (input redirection),
 *					it calls handle_input_redirection(redir->filename).
 *				If the type is T_GREAT (output redirection),
 *					it calls handle_output_redirection(redir->filename).
 *				If the type is T_DGREAT (append redirection),
 *					it calls handle_append_redirection(redir->filename).
 *				If the type is T_DLESS (heredoc redirection),
 *					it calls handle_heredoc_redirection(redir).
 *	Error Propagation:
 *		If any of these functions return a negative value (error),
 *			then the entire function returns -1 immediately.
 *	Return Success:
 *		If all redirections are processed successfully, it returns 0.
 *
 *
 */
