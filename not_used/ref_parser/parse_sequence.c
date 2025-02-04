/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:43:06 by suroh             #+#    #+#             */
/*   Updated: 2025/02/04 22:06:22 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*static bool	consecutive_op_checker(t_parser *parser)
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
		if (consecutive_op_checker(parser))
		{
			parser->consec_error = true;
			return (false);
		}
		if (!token || sequence_is_incomplete(token))
		{	
			parser->incomp_error = true;
			return (false);
		}
	}
	else
		return (false);
}*/

static	t_op_sequence	*add_pipe_to_seq(t_op_sequence *move_seq,
		t_pipe_sequence *pipe)
{
	t_op_sequence	*new_seq;
	t_op_sequence	*tmp;

	new_seq = malloc_t_op_sequence();
	if (!new_seq)
		return (move_seq);
	new_seq->pipe = pipe;
	new_seq->next = NULL;
	if (!move_seq)
		return (new_seq);
	tmp = move_seq;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_seq;
	return (move_seq);
}

t_op_sequence	*parse_sequence(t_parser *parser)
{
	t_op_sequence		*start_seq;
	t_op_sequence		*move_seq;
	t_pipe_sequence		*pipe;
	t_token_node		*token;

	start_seq = NULL;
	move_seq = start_seq;
	token = get_current_token(parser);
	while (1)
	{
		pipe = parse_pipeline(parser);
		if (!pipe)
			break ;
		move_seq = add_pipe_to_seq(move_seq, pipe);
		if (!move_seq)
			break ;
//		if (!incomplete_input_checker(parser))
//			break ;
		advance_token(parser);
		token = get_current_token(parser);
		if (!token)
			break ;
	}
	return (move_seq);
}
