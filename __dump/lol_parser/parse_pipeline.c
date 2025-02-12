/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:21:58 by suroh             #+#    #+#             */
/*   Updated: 2025/02/04 22:22:16 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_pipe_sequence	*add_cmd_to_pipeline(t_pipe_sequence *head,
		t_simple_cmd *cmd)
{
	t_pipe_sequence	*new_node;
	t_pipe_sequence	*tmp;

	new_node = malloc_t_pipe_sequence();
	if (!new_node)
		return (head);
	new_node->cmd = cmd;
	new_node->next = NULL;
	if (!head)
		return (new_node);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (head);
}

t_pipe_sequence	*parse_pipeline(t_parser *parser)
{
	t_pipe_sequence		*pipe;
	t_simple_cmd		*cmd;
	t_token_node		*token;

	pipe = NULL;
	while (1)
	{
		cmd = parse_command(parser);
		if (!cmd)
			break ;
		pipe = add_cmd_to_pipeline(pipe, cmd);
		if (!pipe)
			break ;
		advance_token(parser);
		token = get_current_token(parser);
		if (token && (token->type == T_AND || token->type == T_OR))
			break ;
	}
	return (pipe);
}
