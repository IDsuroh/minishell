/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:42:03 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/31 00:56:26 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_var_elm	*extract_var(char *var)
{
	size_t		key_len;
	char		*value;
	char		*equal;
	t_var_elm	*new_var;

	equal = ft_strchr(var, '=');
	if (equal)
	{
		key_len = equal - var;
		value = ft_strdup(equal + 1);
	}
	else
	{
		key_len = ft_strlen(var);
		value = ft_strdup("");
	}
	new_var = create_var(ft_strndup(var, key_len), value);
	if (new_var)
		new_var->exported = true;
	return (new_var);
}

t_var_elm	*get_value(t_list_header *header, char *key)
{
	t_var_elm	*elm;

	elm = header->head;
	while (elm)
	{
		if (!ft_strcmp(key, elm->key))
			return (elm);
		elm = elm->next;
	}
	return (NULL);
}

t_list_header	*init_var_list(char **envp)
{
	t_list_header	*header;
	t_var_elm		*var;

	header = ft_calloc(1, sizeof(t_list_header));
	if (!header)
		return (NULL);
	if (*envp)
	{
		header->head = extract_var(*envp);
		header->size = 1;
		var = header->head;
	}
	while (*envp && *(++envp))
	{
		var->next = extract_var(*envp);
		if (var->next)
		{
			var->next->prev = var;
			header->size++;
			var = var->next;
		}
	}
	header->tail = var;
	return (header);
}
