/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:24:09 by suroh             #+#    #+#             */
/*   Updated: 2025/01/13 18:40:58 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_node	**tokenizer(char *input)
{
	t_token_node	**tokens_list;
	char			**token_storage;
	int				token_count;

	token_count = 0;
	token_storage = NULL;
	if (!input && is_whitespace(input))
		return (NULL);
	token_count = count_tokens(input);
	token_storage = tokenize_input(input, token_count);
	tokens_list = create_node_list(token_storage, token_count);
	free_tokens(token_storage);
	return (tokens_list);
}
