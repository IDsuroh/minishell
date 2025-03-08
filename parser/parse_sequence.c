/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:57:57 by suroh             #+#    #+#             */
/*   Updated: 2025/03/08 18:21:12 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_op_sequence	*init_existing_token(t_op_sequence *current)
{
	t_op_sequence	*last_node;

	last_node = current;
	last_node->next = malloc_t_op_sequence();
	if (!last_node->next)
		return (NULL);
	last_node->next->prev = last_node;
	last_node = last_node->next;
	return (last_node);
}

static t_op_sequence	*handle_logical_operator(t_parser *parser,
						t_op_sequence *current)
{
	t_token_node	*token;

	token = get_current_token(parser);
	if (!token || (token->type != T_AND && token->type != T_OR))
		return (current);
	advance_token(parser);
	current = init_existing_token(current);
	return (current);
}

t_op_sequence	*parse_sequence(t_parser *parser)
{
	t_op_sequence	*head;
	t_op_sequence	*current;
	t_token_node	*token;

	head = malloc_t_op_sequence();
	if (!head)
		return (NULL);
	current = head;
	token = get_current_token(parser);
	if (!token)
		return (NULL);
	while (token)
	{
		current->pipe = parse_pipe_sequence(parser);
		token = get_current_token(parser);
		if (!token)
			break ;
		current = handle_logical_operator(parser, current);
		if (!current)
			break ;
		token = get_current_token(parser);
	}
	return (head);
}

/*
 * static t_op_sequence	*init_existing_token(t_op_sequence *current)
 * Purpose:
 * 		Given the current op sequence, it allocates a new node,
 * 		links it as the next node (and sets the back reference),
 * 		and returns the new node for further parsing.
 *
 * static t_op_sequence	*handle_logical_operator(t_parser *parser,
 * 						t_op_sequence *current)
 * Purpose:
 * 		Looks at the current token; if it’s a logical operator
 * 		(like && or ||), it advances the token pointer and
 * 		creates a new operation sequence node.
 * 		Uses init_existing_token to allocate and link the new node.
 *
 * t_op_sequence	*parse_sequence(t_parser *parser)
 * Purpose:
 * 		Begins with an initial operation sequence node.
 * 		Enters a loop that parses a “pipe sequence”
 * 		(i.e. commands connected by pipes)
 * 		and then checks for logical operators (&& or ||).
 * 		Calls handle_logical_operator to manage operators that connect
 * 		separate sequences.
 *
 *
 * Why "if (!*tokens)" instead of "if (!tokens)"?
 *
 * When you have a pointer-to-pointer (t_token_node **tokens),
 * using (!*tokens) checks whether the value pointed to by tokens
 * (the actual token pointer) is NULL, while (!tokens) would only check
 * if the pointer-to-pointer itself is NULL. In most cases, the tokens
 * variable itself is always allocated, so dereferenceing it to verify
 * if there's an actual token available is important.
 *
 */
