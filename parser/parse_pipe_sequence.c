/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_sequence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:30:28 by suroh             #+#    #+#             */
/*   Updated: 2025/03/18 17:22:15 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	append_command(t_pipe_sequence **pipe, t_simple_cmd *command)
{
	t_pipe_sequence		*new_pipe;
	t_pipe_sequence		*tmp;

	new_pipe = malloc_t_pipe_sequence();
	if (!new_pipe)
		return ;
	new_pipe->cmd = command;
	new_pipe->next = NULL;
	if (!*pipe)
		return (*pipe = new_pipe, (void)0);
	tmp = *pipe;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_pipe;
}

t_pipe_sequence	*parse_pipe_sequence(t_parser *parser)
{
	t_pipe_sequence		*pipe;
	t_simple_cmd		*command;
	t_token_node		*token;

	pipe = NULL;
	token = get_current_token(parser);
	while (token)
	{
		command = parse_command(parser);
		if (!command)
			return (NULL);
		append_command(&pipe, command);
		token = get_current_token(parser);
		if (!token || (token->type == T_AND || token->type == T_OR))
			break ;
		if (token->type == T_PIPE)
		{
			pipe->cmd->in_pipeline = true;
			advance_token(parser);
			token = get_current_token(parser);
			continue ;
		}
	}
	return (pipe);
}

/*
 * static void	append_command(t_pipe_sequence **pipe, t_simple_cmd *command)
 * Purpose:
 * 		Creates a new pipe sequence node for a given command.
 * 		If the pipe list is empty, it initializes it;
 * 		otherwise, it appends the new node at the end.
 *
 *
 * t_pipe_sequence	*parse_pipe_sequence(t_parser *parser)
 * Purpose:
 *		Parses a series of commands that are connected by the pipe operator.
 * 		It repeatedly calls parse_command to build each command and uses
 * 		append_command to add the command to the pipe sequence.
 * 		It stops when encountering logical operators or
 * 		when no more tokens remain.
 */
