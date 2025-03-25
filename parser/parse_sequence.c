/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:57:57 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 15:47:51 by suroh            ###   ########.fr       */
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
	if (token->type == T_AND)
		current->op = OP_AND;
	else if (token->type == T_OR)
		current->op = OP_OR;
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
