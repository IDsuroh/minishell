/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:53:08 by suroh             #+#    #+#             */
/*   Updated: 2025/02/23 18:58:03 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	append_token_type(char *token_storage)
{
	if (ft_strcmp(token_storage, "|") == 0)
		return (T_PIPE);
	else if (ft_strcmp(token_storage, "||") == 0)
		return (T_OR);
	else if (ft_strcmp(token_storage, ">") == 0)
		return (T_GREAT);
	else if (ft_strcmp(token_storage, ">>") == 0)
		return (T_DGREAT);
	else if (ft_strcmp(token_storage, "<") == 0)
		return (T_LESS);
	else if (ft_strcmp(token_storage, "<<") == 0)
		return (T_DLESS);
	else if (ft_strcmp(token_storage, "&&") == 0)
		return (T_AND);
	else if (ft_strcmp(token_storage, "$?") == 0)
		return (T_XVAR);
	else if (ft_strcmp(token_storage, "$$") == 0)
		return (T_PID);
	else if ((token_storage[0] == '$' && token_storage[1] != ' ')
		|| is_dquote(token_storage))
		return (T_VAR);
	return (T_IDENTIFIER);
}

t_token_node	**create_node_list(char **token_storage, int token_count)
{
	t_token_node	**node_list;
	int				i;

	node_list = ft_calloc(token_count + 1, sizeof(t_token_node *));
	if (!node_list)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		node_list[i] = malloc(sizeof(t_token_node));
		if (!node_list[i])
		{
			free_incomp_node_list(node_list, i);
			return (NULL);
		}
		node_list[i]->token_value = ft_strdup(token_storage[i]);
		node_list[i]->type = append_token_type(node_list[i]->token_value);
		free(token_storage[i]);
		i++;
	}
	free(token_storage);
	node_list[i] = NULL;
	return (node_list);
}

//The create_node_list function creates a double pointer array of
//t_token_node structs. Which will contain the tokens and the types.
//
//next to read: go back to: tokenizer.c

/*static char	*append_token_value(char *token_storage)
{
	char	*token_value;
	int		i;

	if (!token_storage)
		return (NULL);
	i = 0;
	while (token_storage[i] != '\0')
		i++;
	token_value = malloc(sizeof(char) * (i + 1));
	if (!token_value)
		return (NULL);
	i = 0;
	while (token_storage[i] != '\0')
	{
		token_value[i] = token_storage[i];
		i++;
	}
	token_value[i] = '\0';
	return (token_value);
}*/
