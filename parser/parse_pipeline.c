/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:21:58 by suroh             #+#    #+#             */
/*   Updated: 2025/02/01 22:36:23 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	pipe_error_checker(t_parser *parser)
{
	t_token_node	*token;

	token = get_current_token(parser);
	if (token && token->type == T_PIPE)
	{
		advance_token(parser);
		token = get_current_token(parser);
		if (!token || token->type == T_PIPE)
		{
			parser->incomp_error = true;
			return (false);
		}
		return (true);
	}
	else
		return (false);
}

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
		if (!pipe_error_checker(parser))
			break ;
		token = get_next_token(parser);
		if (token && (token->type == T_AND || token->type == T_OR))
			break ;
	}
	return (pipe);
}

/*
 * It will parse a pipeline.
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
 *
 *
 * t_pipe_sequence *parse_pipeline(t_parser *parser)
 *
 * 	t_pipe_sequence *head = NULL; – The start of the pipeline linked list.
 * 	t_simple_cmd *cmd; – Will hold one command.
 * 	t_token_node *token; – Used to check the current token for a pipe.
 *
 * 	while (1) – Loop until we break out of it.
 * 	cmd = parse_command(parser); – Parse a command. (check parse_command.c)
 * 	The head, which is initialzed as NULL, will be assigned the return value
 * 		of add_cmd_to_pipeline(head, cmd).
 * 	
 * 	static t_pipe_sequence *add_cmd_to_pipeline(t_pipe_sequence *head,
 * 		t_simple_cmd *cmd)
 *
 * 		Adds the command to the pipeline linked list.
 * 		assign the return value of create_pipe_sequence() to new_node.
 * 			(check initiators.c)
 * 		Then attach the command to the new_node and initialize the node's
 * 			next to NULL.
 * 		if (!head), it means the pipeline was empty
 * 		
 *
 * token = get_next_token(parser); – Get the next token to see if it is a PIPE.
 * if token = PIPE, then we advance the token, consuming the '|' token
 * and continue the loop.
 *
 * return head; – Return the head of the pipeline linked list.
 */
