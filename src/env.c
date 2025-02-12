/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:42:03 by miteixei          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:36 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// To handle environment variables it is necessary to initialize an address
//   with a copy of all variables provided to the program at startup,
//   and then each time one wants to add, modify, or remove a variable
//   a copy of the double char pointer is to be created, unless no change
//   is going to occur.

// Copy the env pointer to the internal variable list.
// This is supposed to run only once during initialization.
void	copy_vars(const char **envp, char ***var_struct)
{
	size_t	env_size;
	size_t	i;

	env_size = 0;
	while (envp[env_size])
		++env_size;
	*var_struct = malloc((env_size + 1) * sizeof(char **));
	i = 0;
	while (env_size > i++)
		*var_struct[i - 1] = ft_strdup(envp[i - 1]);
	*var_struct[env_size] = NULL;
}

// Simple bool function that checks if the argument name exists in the
//   list and has an equal sign following it.
bool	var_exists(char *arg, char **var_list)
{
	while (*var_list)
	{
		if (!ft_strncmp(*var_list, arg, ft_strlen(arg))
			&& *var_list[ft_strlen(arg)] == '=')
			return (true);
		++var_list;
	}
	return (false);
}

void	var_is_diff(char *arg, char **var_list)
{
	while (*var_list)
	{
		if (!ft_strncmp(*var_list, arg, ft_strlen(arg))
			&& *var_list[ft_strlen(arg)] == '='
			&& ft_strcmp(&(*var_list[ft_strchr(*var_list, '=') + 1]),
				&(arg[ft_strchr(arg, '=') + 1])))
			return (true);
		++var_list;
	}
	return (false);
}

// Remove an variable from the list by copying everything to a new list
//   except the value to be removed.
// If that value isn't on the list do nothing.
void	rem_var(char *arg, char ***var_struct)
{
	char	**old_var;
	char	**new_var;
	size_t	i;

	if (!var_exists(arg, var_struct))
		return ;
	old_var = *var_struct;
	new_var = old_var;
	while (*(new_var++))
		;
	new_var = malloc((new_var - old_var) * sizeof(char **));
	i = 0;
	while (*old_var)
	{
		if (ft_strncmp(*old_var, arg, ft_strlen(arg))
			&& *old_var[ft_strlen(arg)] == '=')
			new_var[i++] = ft_strdup(*old_var);
		++old_var;
	}
	new_var[i] = NULL;
	while (*var_struct)
		free(*((*var_struct)++));
	free(*var_struct);
	*var_struct = new_var;
}

void	add_var(char *arg, char ***var_struct)
{
	char	**old_var;
	char	**new_var;
	size_t	i;

	if (var_exists(arg, var_struct) && !var_is_diff(arg, var_struct))
		return ;
	old_var = *var_struct;
	new_var = old_var;
	while (*(new_var++))
		;
	new_var = malloc((new_var - old_var) * sizeof(char **));
	i = 0;
	while (*old_var)
	{
		if (ft_strncmp(*old_var, arg, ft_strlen(arg)))
			new_var[i++] = ft_strdup(*old_var);
		else if ()
			;
		++old_var;
	}
	new_var[i] = NULL;
	while (*var_struct)
		free(*((*var_struct)++));
	free(*var_struct);
	*var_struct = new_var;
}

// Print the list of strings line by line.
void	_env(char **envp)
{
	while (*envp)
		ft_putstr_fd(*(envp++), 1);
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

void	del_var(t_var_elm **var)
{
	free(*var->key);
	free(*var->value);
	free(*var);
}

void	rem_var(t_var_elm *var, t_list_header *header)
{
	t_var_elm	*prev;
	t_var_elm	*next;

	if (var == header->head) // deal with this
	if (var == header->tail)
	prev = var->prev;
	next = var->next;
	prev->next = next;
	next->prev = prev;
	del_var(&var);
	--(header->size);
}

t_var_elm	*extract_envp(char *envp)
{
	return (create_var(ft_strndup(envp, ft_strchr(envp, '=') - envp),
			ft_strdup(&envp[ft_strchr(envp, '=') - envp])));
}

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
