/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_sequence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:30:28 by suroh             #+#    #+#             */
/*   Updated: 2025/02/17 14:59:11 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_pipe_sequence	*append_command(t_pipe_sequence *pipe,
		t_simple_cmd *command)
{
	t_pipe_sequence		*new_pipe;
	t_pipe_sequence		*tmp;

	new_pipe = malloc_t_pipe_sequence();
	if (!new_pipe)
		return (NULL);
	new_pipe->cmd = command;
	new_pipe->next = NULL;
	if (!pipe)
		return (new_pipe);
	tmp = pipe;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_pipe;
	return (pipe);
}

t_pipe_sequence	*parse_pipe_sequence(t_parser *parser, t_token_node **tokens)
{
	t_pipe_sequence		*pipe;
	t_simple_cmd		*command;

	pipe = NULL;
	while (*tokens)
	{
		command = parse_command(parser, tokens);
		if (!command)
			return (NULL);
		pipe = append_command(pipe, command);
		if (!pipe)
			return (NULL);
		*tokens = get_current_token(parser);
		if (*tokens && ((*tokens)->type == T_AND || (*tokens)->type == T_OR))
			break ;
		if (*tokens && (*tokens)->type == T_PIPE)
		{
			advance_token(parser);
			*tokens = get_current_token(parser);
			continue ;
		}
	}
	return (pipe);
}
