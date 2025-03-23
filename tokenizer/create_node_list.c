/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:53:08 by suroh             #+#    #+#             */
/*   Updated: 2025/03/23 17:37:39 by suroh            ###   ########.fr       */
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
	else if (token_storage[0] == '$'
		|| (is_var_dquote(token_storage) && ft_strchr(token_storage, '$')
			&& is_quote_closed(token_storage)))
		return (T_VAR);
	return (T_IDENTIFIER);
}

static t_token_node	*create_token_node(char *tok_str, int pos, bool adjacent)
{
	t_token_node	*node;

	node = malloc(sizeof(t_token_node));
	if (!node)
		return (NULL);
	node->token_value = ft_strdup(tok_str);
	if (!node->token_value)
	{
		free(node);
		return (NULL);
	}
	node->type = append_token_type(node->token_value);
	node->start_idx = pos;
	node->adjacent = adjacent;
	return (node);
}

static bool	compute_adjacent_flag(int i, int *pos, char **token_storage)
{
	int	prev_end;

	if (i <= 0)
		return (false);
	prev_end = pos[i - 1] + ft_strlen(token_storage[i - 1]);
	return (pos[i] == prev_end);
}

static void	free_tokstor(char **token_storage)
{
	int	i;

	i = -1;
	while (token_storage[++i])
		free(token_storage[i]);
	free(token_storage);
}

t_token_node	**create_node_list(char **token_storage, int token_count,
					int *pos)
{
	t_token_node	**node_list;
	int				i;
	bool			adjacent;

	node_list = ft_calloc(token_count + 1, sizeof(t_token_node *));
	if (!node_list)
		return (NULL);
	i = -1;
	while (++i < token_count && token_storage[i])
	{
		if (i > 0)
			adjacent = compute_adjacent_flag(i, pos, token_storage);
		else
			adjacent = false;
		node_list[i] = create_token_node(token_storage[i], pos[i], adjacent);
		if (!node_list[i])
		{
			free_incomp_node_list(node_list, i);
			return (NULL);
		}
	}
	node_list[i] = NULL;
	free_tokstor(token_storage);
	return (node_list);
}

/*
 * static int	append_token_type(char *token_storage)
 * Purpose:
 * 		Maps a token string (from the raw token storage) to a corresponding
 * 		token type (like pipe, redirection, variable, etc.).
 * 		
 * 		 - It sequentially compares the token string against known tokens
 * 			using ft_strcmp.
 * 		 - Additionally, if the token starts with a dollar sign ($) or
 * 		 	meets the conditions for a variable in a double-quoted context
 * 		 	(using helper functions like is_var_dquote and is_quote_closed),
 * 		 	it returns T_VAR.
 *
 *
 * t_token_node	**create_node_list(char **token_storage, int token_count)
 * Purpose:
 * 		Converts an array of token strings (token_storage) into an array
 * 		of token nodes (t_token_node pointers) by allocating memory,
 * 		duplicating the token strings, and assigning a token type to each node.
 *
 *		 - Uses ft_strdup to duplicate the token string and assigns it
 *		 	to the token_value field of the node.
 *
 *				*go back to tokenizer.c then main.c located in the src directory.
 */
