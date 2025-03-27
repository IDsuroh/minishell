/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:55:54 by suroh             #+#    #+#             */
/*   Updated: 2025/03/27 22:22:05 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	validate_command_tokens(t_simple_cmd *cmd)
{
	size_t	i;

	if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (false);
	i = 0;
	while (cmd->argv[0][i])
	{
		if (!ft_isdigit(cmd->argv[0][i]))
			break ;
		i++;
	}
	if (i == ft_strlen(cmd->argv[0]))
		return (false);
	return (true);
}

void	restore_stdin_to_tty(void)
{
	int	tty_fd;

	if (!isatty(STDIN_FILENO))
	{
		tty_fd = open("/dev/tty", O_RDONLY);
		if (tty_fd < 0)
		{
			perror("open /dev/ tty");
			exit(EXIT_FAILURE);
		}
		if (dup2(tty_fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(tty_fd);
			exit(EXIT_FAILURE);
		}
		close(tty_fd);
	}
}

void	free_pid_list(t_pid_node *acpl)
{
	t_pid_node	*tmp;

	while (acpl)
	{
		tmp = acpl;
		acpl = acpl->next;
		free(tmp);
	}
}
