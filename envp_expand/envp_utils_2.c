/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:58:58 by suroh             #+#    #+#             */
/*   Updated: 2025/03/27 22:22:14 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_var_list(t_list_header *header)
{
	t_var_elm	*current;
	t_var_elm	*next;

	current = header->head;
	while (current)
	{
		next = current->next;
		del_var(current);
		current = next;
	}
	free(header);
}

void	free_envp_array(char **envp, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
