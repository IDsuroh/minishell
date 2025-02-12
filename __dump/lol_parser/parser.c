/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:27:33 by suroh             #+#    #+#             */
/*   Updated: 2025/02/04 22:15:33 by suroh            ###   ########.fr       */
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
