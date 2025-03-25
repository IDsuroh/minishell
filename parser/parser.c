/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:53:55 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 15:47:57 by suroh            ###   ########.fr       */
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
