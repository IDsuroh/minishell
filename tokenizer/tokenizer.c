/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:24:09 by suroh             #+#    #+#             */
/*   Updated: 2025/02/18 22:33:47 by suroh            ###   ########.fr       */
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
	if (!input || is_whitespace(input))
		return (NULL);
	token_count = count_tokens(input);
	token_storage = tokenize_input(input, token_count);
	tokens_list = create_node_list(token_storage, token_count);
	token_count = 0;
	return (tokens_list);
}

//The start of the Tokenizer process: Custom Lexer Program.
//					AKA Lexical Analyzer.
//token_count:	count_tokens(input)
//	- Count the number of tokens in the input string.
//
//token_storage:	tokenize_input(input, token_count)
//	- Store the tokens in an array of strings.
//
//tokens_list:	create_node_list(token_storage, token_count)
//	- Store the tokens in a double pointer array of t_token_node structs.
//	- Each t_token_node struct contains a token string and a token type.
//
//The function returns the tokens_list.
//
//The flags and the helper functions will not be explained
//	due to the simplicity.
