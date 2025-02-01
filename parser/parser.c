/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:27:33 by suroh             #+#    #+#             */
/*   Updated: 2025/01/31 18:29:33 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_op_sequence	*parse_tokens(t_token_node **tokens)
{
	t_parser	parser;

	parser.tokens = tokens;
	parser.cur_idx = 0;
	parser.incomp_error = false;
	parser.consec_error = false;
	parser.redir_error = false;
	return (parse_operators(&parser));
}

/*
 * The start of the parsing process. It will parse a sequence.
 * A sequence of pipe structures which looks like this;
 * 	
 * 	typedef struct	s_pipe_sequence
 *	{
 *		t_simple_cmd				*cmd;
 *		struct s_pipe_sequence		*next;
 *	}	t_pipe_sequence;
 *
 * Into this;
 *
 * 	typedef struct	s_op_sequence
 * 	{
 * 		t_pipe_sequence			*pipe;
 * 		t_token_type			otype;
 * 		struct s_op_sequence	*next;
 * 	}	t_op_sequence;
 * 
 * It will return a pointer to the head of the sequence.
 * Which will be the last of the linked list.
 */
