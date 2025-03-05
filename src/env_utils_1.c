/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:10:39 by suroh             #+#    #+#             */
/*   Updated: 2025/03/04 20:15:32 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Print the list of strings line by line.
void	print_vars(char **envp)
{
	while (*envp)
		ft_putstr_fd(*(envp++), 1);
}

t_var_elm	*create_var(char *key, char *value)
{
	t_var_elm	*var;

	if (!key)
		return (NULL);
	var = malloc(sizeof(t_var_elm));
	var->key = key;
	var->value = value;
	var->prev = NULL;
	var->next = NULL;
	return (var);
}

void	add_var(t_list_header *header, t_var_elm *var)
{
	t_var_elm	*elm;

	elm = get_value(header, var->key);
	if (!elm)
	{
		var = header->tail->next;
		header->tail = var;
	}
	else
	{
		elm->value = ft_strdup(var->value);
		del_var(var);
	}
}

void	del_var(t_var_elm *var)
{
	free(var->key);
	free(var->value);
	free(var);
}

void	rem_var(t_list_header *header, t_var_elm *var)
{
	t_var_elm	*prev;
	t_var_elm	*next;

	if (!var)
		return ;
	prev = var->prev;
	next = var->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (var == header->head)
		header->head = var->next;
	if (var == header->tail)
		header->tail = var->prev;
	del_var(var);
	--(header->size);
}
