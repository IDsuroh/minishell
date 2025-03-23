/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:10:39 by suroh             #+#    #+#             */
/*   Updated: 2025/03/23 20:37:20 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
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
		insert_new_var(header, var);
	else
		update_existing_var(elm, var);
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
