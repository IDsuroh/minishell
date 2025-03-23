/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:24:09 by suroh             #+#    #+#             */
/*   Updated: 2025/03/23 18:18:28 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_node	**tokenizer(char *input)
{
	t_token_node	**tokens_list;
	char			**token_storage;
	int				token_count;
	int				*pos;

	token_count = 0;
	token_storage = NULL;
	if (!input || is_whitespace(input))
		return (NULL);
	token_count = count_tokens(input);
	pos = (int *)ft_calloc(token_count, sizeof(int));
	if (!pos)
		return (NULL);
	token_storage = tokenize_input(input, token_count, pos);
	tokens_list = create_node_list(token_storage, token_count, pos);
	process_quote_rem_and_concat(tokens_list);
	token_count = -1;
	free(pos);
	return (tokens_list);
}

/*
 * where the inputs become tokens
 * it will return a double pointer to the structure t_token_node
 * which will look like this:
 *
 * 		typedef struct s_token_node
 * 		{
 * 		t_token_type		type;
 *		char				*token_value;
 *		}	t_token_node;
 *
 *	It is not a linked list. The double pointer is set simple in the purpose
 *	to easily iterate later using ints with while loops.
 *
 *	The token_count is important because it will work as our iterator later
 *	when we have to put types and values in the double pointed lists.
 *
 *	So first we count how many tokens there should be,
 *	then store the tokens as an array of strings,
 *	then after we create the double pointed lists using those two assets.
 *
 *			*files to check:
 *				./tokenizer_counter.c
 *				./tokenize_input.c
 *				./create_node_list.c
 *
 */
