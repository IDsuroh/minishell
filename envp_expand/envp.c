/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:42:03 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/25 20:59:16 by suroh            ###   ########.fr       */
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
