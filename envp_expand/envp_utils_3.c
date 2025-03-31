/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:25:36 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 16:08:47 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	insert_new_var(t_list_header *header, t_var_elm *var)
{
	if (!header->head || header->tail == NULL)
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

void	update_existing_var(t_var_elm *node, char *key, char *value)
{
	free(node->value);
	node->value = value;
	node->exported = true;
	free(key);
}
