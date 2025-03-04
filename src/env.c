/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:42:03 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/05 14:28:30 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// To handle environment variables it is necessary to initialize an address
//   with a copy of all variables provided to the program at startup,
//   and then each time one wants to add, modify, or remove a variable
//   a copy of the double char pointer is to be created, unless no change
//   is going to occur.

char	**make_envp(t_list_header *header)
{
	t_var_elm	*elm;
	char		**envp;
	size_t		i;

	elm = header->head;
	envp = malloc((header->size + 1) * sizeof(char *));
	i = 0;
	while (elm)
	{
		envp[i] = malloc((ft_strlen(elm->key) + 1 + ft_strlen(elm->value) + 1)
				* sizeof(char));
		ft_strlcpy(envp[i], elm->key, ft_strlen(elm->key) + 1);
		ft_strlcpy(&envp[i][ft_strlen(elm->key)], "=", 2);
		ft_strlcpy(&envp[i][ft_strlen(elm->key) + 1], elm->value,
			ft_strlen(elm->value) + 1);
		elm = elm->next;
		++i;
	}
	envp[i] = NULL;
	return (envp);
}

t_var_elm	*extract_var(char *var)
{
	return (create_var(ft_strndup(var, ft_strchr(var, '=') - var),
			ft_strdup(&var[ft_strchr(var, '=') - var])));
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

// init the var list with each envp string
//   by splitting them into key value pairs
// this is run once during the shell's initialization
t_list_header	*init_var_list(char **envp)
{
	t_list_header	*header;
	t_var_elm		*var;

	header = malloc(sizeof(t_list_header));
	header->size = 0;
	header->head = extract_var(*envp);
	++(header->size);
	var = header->head;
	while (*(++envp))
	{
		var->next = extract_var(*envp);
		var->next->prev = var;
		++(header->size);
		if (var->next)
			var = var->next;
	}
	header->tail = var;
	return (header);
}
