/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:27:33 by suroh             #+#    #+#             */
/*   Updated: 2025/01/29 17:36:41 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe_sequence	*parse_tokens(t_token_node **tokens)
{
	t_parser	parser;

	parser.tokens = tokens;
	parser.cur_idx = 0;
	parser.error = false;
	return (parse_pipeline(&parser));
}

/*
 * The start of the parsing process. It will parse a pipeline.
 * A pipe structure which looks like this;
 * 	
 * 	typedef struct	s_pipe_sequence
 *	{
 *		t_simple_cmd				*cmd;
 *		struct s_pipe_sequence		*next;
 *	}	t_pipe_sequence;
 *
 * It will return a pointer to the head of the pipeline.
 * Which will be the last of the linked list.
 */
