/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:43:06 by suroh             #+#    #+#             */
/*   Updated: 2025/02/01 23:20:39 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	consecutive_op_checker(t_parser *parser)
{
	t_token_node	*cur;
	t_token_node	*next;

	cur = get_current_token(parser);
	if (!cur)
		return (false);
	next = get_next_token(parser);
	if (!next)
		return (false);
	if (cur->type == next->type)
		return (true);
	if (cur->type == T_PIPE || cur->type == T_AND || cur->type == T_OR)
	{
		if (next->type == T_PIPE || next->type == T_AND || next->type == T_OR)
			return (true);
	}
	return (false);
}

static bool	sequence_is_incomplete(t_token_node *token)
{
	return (token->token_value[0] == ' ' || token->token_value[0] == '\t'
		|| token->token_value[0] == '\n' || token->token_value[0] == '\0');
}

static bool	incomplete_input_checker(t_parser *parser)
{
	t_token_node	*token;

	token = get_current_token(parser);
	if (token && (token->type == T_AND || token->type == T_OR))
	{
		advance_token(parser);
		token = get_current_token(parser);
		if (!token || sequence_is_incomplete(token))
		{	
			parser->incomp_error = true;
			return (false);
		}
		if (consecutive_op_checker(parser))
		{
			parser->consec_error = true;
			return (false);
		}
		return (true);
	}
	else
		return (false);
}

static	t_op_sequence	*add_pipe_to_seq(t_op_sequence *ops,
		t_pipe_sequence *pipe)
{
	t_op_sequence	*new_node;
	t_op_sequence	*tmp;

	new_node = malloc_t_op_sequence();
	if (!new_node)
		return (ops);
	new_node->pipe = pipe;
	new_node->next = NULL;
	if (!ops)
		return (new_node);
	tmp = ops;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (ops);
}

t_op_sequence	*parse_operators(t_parser *parser)
{
	t_op_sequence		*ops;
	t_pipe_sequence		*pipe;

	ops = NULL;
	while (1)
	{
		pipe = parse_pipeline(parser);
		if (!pipe)
			break ;
		ops = add_pipe_to_seq(ops, pipe);
		if (!ops)
			break ;
		if (!incomplete_input_checker(parser))
			break ;
	}
	return (ops);
}
