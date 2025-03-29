/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_command_helper.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:51:35 by suroh             #+#    #+#             */
/*   Updated: 2025/03/26 19:57:17 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_cmd_not_found(t_simple_cmd *cmd, t_almighty *mighty,
		char *exec_path)
{
	write(STDERR_FILENO, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
	mighty->exit_stat = 127;
	if (exec_path)
		free(exec_path);
	free_all(mighty);
	free(mighty);
	exit(127);
}

void	handle_dir_error(t_almighty *mighty, char *exec_path)
{
	write(STDERR_FILENO, exec_path, ft_strlen(exec_path));
	write(STDERR_FILENO, ": Is a directory\n", 17);
	mighty->exit_stat = 126;
	free(exec_path);
	free_all(mighty);
	free(mighty);
	exit(126);
}

void	handle_no_file_error(t_almighty *mighty, char *exec_path)
{
	write(STDERR_FILENO, exec_path, ft_strlen(exec_path));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
	mighty->exit_stat = 127;
	free(exec_path);
	free_all(mighty);
	free(mighty);
	exit(127);
}

void	check_executable_status(t_simple_cmd *cmd, t_almighty *mighty,
		char *exec_path)
{
	struct stat	st;

	if (ft_strchr(cmd->argv[0], '/') != NULL)
	{
		if (stat(exec_path, &st) != 0)
			handle_no_file_error(mighty, exec_path);
		else if (S_ISDIR(st.st_mode))
			handle_dir_error(mighty, exec_path);
		else if (access(exec_path, X_OK) != 0)
		{
			perror(exec_path);
			free(exec_path);
			free_all(mighty);
			free(mighty);
			exit(126);
		}
	}
	else
	{
		if (stat(exec_path, &st) != 0 || access(exec_path, X_OK) != 0)
			handle_cmd_not_found(cmd, mighty, exec_path);
		else if (S_ISDIR(st.st_mode))
			handle_cmd_not_found(cmd, mighty, exec_path);
	}
}

void	handle_exec_failure(char *exec_path)
{
	perror("execve");
	free(exec_path);
	if (errno == EACCES)
		exit(126);
	exit(127);
}
