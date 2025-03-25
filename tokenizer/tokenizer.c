/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:24:09 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 21:02:08 by suroh            ###   ########.fr       */
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
