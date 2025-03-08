/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:53:55 by suroh             #+#    #+#             */
/*   Updated: 2025/03/08 18:18:03 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_parser(t_parser *parser, t_token_node **tokens)
{
	parser->tokens = tokens;
	parser->cur_idx = 0;
}

t_op_sequence	*parse_tokens(t_token_node **tokens)
{
	t_parser		*parser;
	t_op_sequence	*sequence;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	init_parser(parser, tokens);
	sequence = parse_sequence(parser);
	parser->cur_idx = 0;
	free(parser);
	return (sequence);
}

/*
 * static void	init_parser(t_parser *parser, t_token_node **tokens)
 * Purpose:
 * 		Sets up a parser structure by assigning the tokens and
 * 		initializing the current index to zero.
 *
 * t_op_sequence	*parse_tokens(t_token_node **tokens)
 * Purpose:
 * 		Allocates and initializes a parser. Calls parse_sequence
 * 		to build an operation sequence from the tokens. Frees
 * 		the temporary parser structure before returning the parsed sequence.
 *
 * the struct t_op_sequence is constructed into a linked list.
 *		
 *		typedef struct s_op_sequence
 *		{
 * 		t_pipe_sequence				*pipe;
 * 		struct s_op_sequence		*next;
 * 		struct s_op_sequence		*prev;
 * 		}	t_op_sequence;
 *
 * The functionality of the struct t_parser is simply to utilize the tokens.
 * and the index number of the tokens.
 *
 *		typedef struct s_parser
 *		{
 *		t_token_node	**tokens;
 *		int				cur_idx;
 *		}	t_parser;
 *
 *
 * The sequence will be the returned result.
 */
