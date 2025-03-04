/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:57:57 by suroh             #+#    #+#             */
/*   Updated: 2025/02/24 22:45:18 by suroh            ###   ########.fr       */
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
	t_token_node	*curr;

	curr = get_current_token(parser);
	if (!curr || (curr->type != T_AND && curr->type != T_OR))
		return (current);
	advance_token(parser);
	current = init_existing_token(current);
	return (current);
}

t_op_sequence	*parse_sequence(t_parser *parser)
{
	t_op_sequence	*head;
	t_op_sequence	*current;
	t_token_node	*curr;

	head = malloc_t_op_sequence();
	if (!head)
		return (NULL);
	current = head;
	curr = get_current_token(parser);
	if (!curr)
		return (NULL);
	while (curr)
	{
		current->pipe = parse_pipe_sequence(parser);
		curr = get_current_token(parser);
		if (!curr)
			break ;
		current = handle_logical_operator(parser, current);
		if (!current)
			break ;
		curr = get_current_token(parser);
	}
	return (head);
}

/*
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
