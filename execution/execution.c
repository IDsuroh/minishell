/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:04:19 by suroh             #+#    #+#             */
/*   Updated: 2025/03/05 18:42:15 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_last_exit_status;

/*void	execute_command(t_op_sequence *tmp_seq)
{
	pid_t			pid;
	int				status;
	t_simple_cmd	*cmd;
	t_redir			*redir;
	int				fd;

	pid = fork();
	if (pid == 0)
	{
		if (execve(tmp_seq->argv[0], tmp_seq->argv, tmp_seq->envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);
		else
			g_last_exit_status = 1;
	}
	else
	{
		perror("fork");
		g_last_exit_status = 1;
	}
}*/
