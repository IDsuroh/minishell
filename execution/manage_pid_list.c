/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pid_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:46:18 by suroh             #+#    #+#             */
/*   Updated: 2025/03/15 16:22:36 by suroh            ###   ########.fr       */
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
	new_node->next = mighty->acpl;
	mighty->acpl = new_node;
}

void	remove_child_pid(t_almighty *mighty, pid_t pid)
{
	t_pid_node	**curr;
	t_pid_node	*tmp;

	curr = &mighty->acpl;
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

	curr = mighty->acpl;
	while (curr)
	{
		kill(curr->pid, sig);
		curr = curr->next;
	}
}

/*
 * void	add_child_pid(t_almighty *mighty, pid_t pid)
 * 	Purpose:
 * 		Adds a child process ID (PID) to the linked list stored
 * 			in your t_almighty structure (here, acpl).
 * 	How It Works:
 * 		Memory Allocation:
 * 			Allocates a new node of type t_pid_node.
 * 		Error Handling:
 * 			If malloc fails, perror("malloc") prints an error
 * 				message and the program exits with EXIT_FAILURE.
 * 		Insertion:
 * 			Sets the node’s pid to the given pid and prepends
 * 				it to the linked list (mighty->acpl).
 *
 *
 * void	remove_child_pid(t_almighty *mighty, pid_t pid)
 *  Purpose:
 *  	Removes a child PID from the linked list when
 *  	the child process terminates.
 *  How It Works:
 *      Traversal:
 *      	Uses a pointer-to-pointer (t_pid_node **curr)
 *      		to traverse the list.
 *      Deletion:
 *      	When a node with the matching PID is found,
 *      	it is removed from the list and its memory is freed.
 *      Return:
 *      	Returns immediately after deleting the node.
 *
 *
 * void	send_signal_to_all_children(t_almighty *mighty, int sig)
 *  Purpose:
 *  	Sends a specified signal (sig) to every active child process
 *  		tracked in the t_almighty structure.
 *  How It Works:
 *  	Iteration:
 *  		Iterates over the linked list (mighty->acpl) of child PIDs.
 *  	Signal Sending:
 *  		Uses the kill() system call to send the signal to each
 *  			child's PID.
 *  	Usage:
 *  		This function is called when, for example, the user presses
 *  			Ctrl+C (SIGINT), and you need to forward that signal
 *  			to all child processes.
 *
 *			* currently not using this function, but might use in the
 *			* future. Using terminal_interrupt for the moment.
 *
 *
 *
 *
 */
