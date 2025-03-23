/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:25:36 by suroh             #+#    #+#             */
/*   Updated: 2025/03/23 20:35:10 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	insert_new_var(t_list_header *header, t_var_elm *var)
{
	if (!header->head)
	{
		header->head = var;
		header->tail = var;
	}
	else
	{
		header->tail->next = var;
		var->prev = header->tail;
		header->tail = var;
	}
	header->size++;
}

void	update_existing_var(t_var_elm *existing, t_var_elm *new_var)
{
	free(existing->value);
	if (new_var->value)
		existing->value = ft_strdup(new_var->value);
	else
		existing->value = NULL;
	del_var(new_var);
}
