/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:27:33 by suroh             #+#    #+#             */
/*   Updated: 2025/02/04 22:10:33 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	t_parser	*init_parser(t_token_node **tokens)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->tokens = tokens;
	parser->cur_idx = 0;
	parser->pipe_open = false;
	parser->cmdand_open = false;
	parser->cmdor_open = false;
	parser->consec_error = false;
	parser->redir_error = false;
	return (parser);
}

t_op_sequence	*parse_tokens(t_token_node **tokens)
{
	t_parser	*parser;

	parser = init_parser(tokens);
	return (parse_sequence(parser));
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
