/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:42:03 by miteixei          #+#    #+#             */
/*   Updated: 2025/02/22 21:11:31 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// To handle environment variables it is necessary to initialize an address
//   with a copy of all variables provided to the program at startup,
//   and then each time one wants to add, modify, or remove a variable
//   a copy of the double char pointer is to be created, unless no change
//   is going to occur.

// Print the list of strings line by line.
void	_env(char **envp)
{
	while (*envp)
		ft_putstr_fd(*(envp++), 1);
}

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

t_var_elm	create_var(char *key, char *value)
{
	t_var_elm	*var;

	if (!key || !value)
		return (NULL);
	var = malloc(sizeof(t_var_elm));
	var->key = key;
	var->value = value;
	var->prev = NULL;
	var->next = NULL;
	return (var);
}

void	del_var(t_var_elm *var)
{
	free(var->key);
	free(var->value);
	free(var);
}

void	rem_var(t_var_elm *var, t_list_header *header)
{
	t_var_elm	*prev;
	t_var_elm	*next;

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

t_var_elm	*extract_envp(char *envp)
{
	return (create_var(ft_strndup(envp, ft_strchr(envp, '=') - envp),
			ft_strdup(&envp[ft_strchr(envp, '=') - envp])));
}

char	*get_value(t_list_header *header, char *key)
{
	t_var_elm	*elm;

	elm = header->head;
	while (elm)
	{
		if (!ft_strcmp(key, elm->key))
			return (elm->value);
		elm = elm->next;
	}
	return (NULL);
}

t_list_header	*init_var_list(char **envp)
{
	t_list_header	*header;
	t_var_elm		*var;

	header = malloc(sizeof(t_list_header));
	header->size = 0;
	header->head = extract_envp(*envp);
	++(header->size);
	var = header->head;
	while (*(++envp))
	{
		var->next = extract_envp(*envp);
		var->next->prev = var;
		++(header->size);
		if (var->next)
			var = var->next;
	}
	header->tail = var;
	return (header);
}
