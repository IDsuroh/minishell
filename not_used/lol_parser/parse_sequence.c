/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:43:06 by suroh             #+#    #+#             */
/*   Updated: 2025/02/04 22:16:21 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		advance_token(parser);
		token = get_current_token(parser);
		if (!token)
			break ;
	}
	return (move_seq);
}
