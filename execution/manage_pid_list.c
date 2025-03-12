/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pid_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:46:18 by suroh             #+#    #+#             */
/*   Updated: 2025/03/11 19:03:03 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_child_pid(t_almighty *mighty, pid_t pid)
{
	t_pid_node	*new_node;

	new_node = malloc(sizeof(t_pid_node));
	if (!new_node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_node->pid = pid;
	new_node->next = mighty->active_child_pid_list;
	mighty->active_child_pid_list = new_node;
}

void	remove_child_pid(t_almighty *mighty, pid_t pid)
{
	t_pid_node	**curr;
	t_pid_node	*tmp;

	curr = &mighty->active_child_pid_list;
	while (*curr)
	{
		if ((*curr)->pid == pid)
		{
			tmp = *curr;
			*curr = (*curr)->next;
			free(tmp);
			return ;
		}
		curr = &((*curr)->next);
	}
}

void	send_signal_to_all_children(t_almighty *mighty, int sig)
{
	t_pid_node	*curr;

	curr = mighty->active_child_pid_list;
	while (curr)
	{
		kill(curr->pid, sig);
		curr = curr->next;
	}
}
