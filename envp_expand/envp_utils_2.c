/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:58:58 by suroh             #+#    #+#             */
/*   Updated: 2025/03/14 20:56:04 by miteixei         ###   ########.fr       */
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
