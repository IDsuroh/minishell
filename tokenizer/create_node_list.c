/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:53:08 by suroh             #+#    #+#             */
/*   Updated: 2025/01/13 19:05:59 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	append_token_type(char *token_storage)
{
	if (!token_storage)
		return (T_IDENTIFIER);
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
	else if (ft_strcmp(token_storage, "$") == 0)
		return (T_VAR);
	else if (ft_strcmp(token_storage, "$?") == 0)
		return (T_XVAR);
	else
		return (T_IDENTIFIER);
}

static char	*append_token_value(char *token_storage)
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
}

t_token_node	**create_node_list(char **token_storage, int token_count)
{
	t_token_node	**node_list;
	int				i;

	node_list = malloc(sizeof(t_token_node *) * (token_count + 1));
	if (!node_list)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		node_list[i] = malloc(sizeof(t_token_node));
		if (!node_list[i])
		{
			if (i > 0)
				free_node_list(node_list);
			return (NULL);
		}
		node_list[i]->token_value = append_token_value(token_storage[i]);
		node_list[i]->type = append_token_type(token_storage[i]);
		i++;
	}
	node_list[i] = NULL;
	return (node_list);
}
