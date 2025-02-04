/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:57:57 by suroh             #+#    #+#             */
/*   Updated: 2025/02/04 20:02:41 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	t_op_sequence	*link_and_advance_sequence(t_op_sequence *op_seq)
{
	t_op_sequence	*new_op_seq;

	new_op_seq = malloc_t_op_sequence();
	if (!new_op_seq)
		return (NULL);
	new_op_seq->pipe = NULL;
	new_op_seq->next = NULL;
	if (op_seq)
	{
		new_op_seq->prev = op_seq;
		op_seq->next = new_op_seq;
	}
	else
		new_op_seq->prev = NULL;
	return (new_op_seq);
}

static	t_op_sequence	*append_pipe(t_op_sequence *op_seq,
					t_pipe_sequence *pipe)
{
	t_op_sequence	*new_op_seq;
	t_op_sequence	*tmp;

	new_op_seq = malloc_t_op_sequence();
	if (!new_op_seq)
		return (NULL);
	new_op_seq->pipe = pipe;
	new_op_seq->next = NULL;
	new_op_seq->prev = NULL;
	if (!op_seq)
		return (new_op_seq);
	tmp = op_seq;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_op_seq;
	new_op_seq->prev = tmp;
	return (op_seq);
}

static	t_op_sequence	*return_to_start(t_op_sequence *op_seq)
{
	while (op_seq->prev)
		op_seq = op_seq->prev;
	return (op_seq);
}

t_op_sequence	*parse_sequence(t_parser *parser, t_token_node **tokens)
{
	t_op_sequence		*op_seq;
	t_pipe_sequence		*pipe;

	op_seq = NULL;
	*tokens = get_current_token(parser);
	while (*tokens)
	{
		if (*tokens && ((*tokens)->type == T_AND || (*tokens)->type == T_OR))
		{
			op_seq = link_and_advance_sequence(op_seq);
			advance_token(parser);
			*tokens = get_current_token(parser);
			continue ;
		}
		pipe = parse_pipe_sequence(parser, tokens);
		op_seq = append_pipe(op_seq, pipe);
		advance_token(parser);
		*tokens = get_current_token(parser);
	}
	op_seq = return_to_start(op_seq);
	return (op_seq);
}
