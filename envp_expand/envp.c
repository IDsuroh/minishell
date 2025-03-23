/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:42:03 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/23 21:21:20 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (!envp[i])
		{
			free_envp_array(envp, i);
			return (NULL);
		}
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
	size_t	key_len;
	char	*value;

	key_len = ft_strchr(var, '=') - var;
	if (ft_strchr(var, '='))
		value = ft_strdup(&var[key_len + 1]);
	else
		value = ft_strdup("");
	return (create_var(ft_strndup(var, key_len), value));
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

// To handle environment variables it is necessary to initialize an address
//   with a copy of all variables provided to the program at startup,
//   and then each time one wants to add, modify, or remove a variable
//   a copy of the double char pointer is to be created, unless no change
//   is going to occur.
/*
 * char	**make_envp(t_list_header *header)
 * Purpose:
 * 		Reconstructs an environment pointer array (char **envp)
 * 		from the linked list of environment variables which
 * 		holds the information of the environment variables.
 *
 * 		typedef struct s_list_header
 * 		{
 * 		t_var_elm	*head;
 * 		t_var_elm	*tail;
 * 		int			size;
 * 		}	t_list_header;
 *
 * 		typedef struct s_var_elm
 * 		{
 * 		char				*key;
 * 		char				*value;
 * 		struct s_var_elm	*prev;
 * 		struct s_var_elm	*next;
 * 		}	t_var_elm;
 *
 * How It Works:
 * 		Allocates an array of pointers, one for each
 * 		environment variable plus one extra for
 * 		the terminating NULL.
 * 		For each node in the list, it allocates enough
 * 		space to store a string in the format "key=value".
 * 		Uses string copy functions (ft_strlcpy) to copy the key,
 * 		add the "=" separator, and then copy the value.
 * 		Returns the completed array.
 *
 *
 * t_var_elm	*extract_var(char *var)
 * Purpose:
 * 		Splits an environment string (for example, "PATH=/usr/bin")
 * 		into its key and value parts, and creates a new environment
 * 		variable node.
 *
 * 	How It Works:
 *
 * 		Key Extraction:
 * 				Uses ft_strndup to duplicate the substring from the start
 * 				of the string up to (but not including) the '=' character.
 * 		Value Extraction:
 * 				Uses ft_strdup to duplicate the substring starting at
 * 				the '=' character. (Often, you might expect this to start
 * 				after the '='; however, this implementation copies from
 * 				the '=' onward.)
 * 		Calls create_var (assumed to allocate and initialize a t_var_elm node)
 * 				with the key and value.
 * 
 *
 * t_var_elm	*get_value(t_list_header *header, char *key)
 * Purpose:
 * 		Searches for an environment variable in the list by its key.
 *
 * 	How It Works:
 *
 * 		Iterates through the linked list starting from the head.
 * 		Compares each node’s key with the provided key using ft_strcmp.
 * 		Returns the node if a match is found; otherwise, returns NULL.
 *
// init the var list with each envp string
//   by splitting them into key value pairs
// this is run once during the shell's initialization
 * t_list_header	*init_var_list(char **envp)
 * Purpose:
 * 		Initializes the environment variable list from the array of
 * 		environment strings (envp), which is usually passed to
 * 		the program at startup.
 *
 * How It Works:
 * 	
 * 	Allocates a new t_list_header and sets its initial size to zero.
 * 	Extracts the first environment variable with extract_var and
 * 	sets it as the head of the list.
 * 	Iterates through the remaining environment strings:
 * 		For each string, creates a new node.
 * 		Links it to the previous node using the prev pointer.
 * 		Increments the list’s size.
 * 	After the loop, sets the tail pointer to the last node.
 * 	Returns the initialized list header.
 */
