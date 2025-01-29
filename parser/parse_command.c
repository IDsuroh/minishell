/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:28:53 by suroh             #+#    #+#             */
/*   Updated: 2025/01/29 19:17:24 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	handle_argv(t_simple_cmd *cmd, t_parser *parser)
{
	t_token_node	*token;

	token = get_current_token(parser);
	if (!token || (token->type != T_IDENTIFIER && token->type != T_VAR
			&& token->type != T_XVAR && token->type != T_PID))
		return (false);
	if (!append_argv(cmd, token->token_value))
		return (false);
	advance_token(parser);
	return (true);
}

static bool	handle_redir(t_simple_cmd *cmd, t_parser *parser)
{
	t_token_node	*token;
	t_token_node	*file_token;
	t_token_type	rtype;

	token = get_current_token(parser);
	if (!token || (token->type != T_LESS && token->type != T_GREAT
			&& token->type != T_DLESS && token->type != T_DGREAT))
		return (false);
	rtype = token->type;
	advance_token(parser);
	file_token = get_current_token(parser);
	if (!file_token || (file_token->type != T_IDENTIFIER
			&& file_token->type != T_VAR && file_token->type != T_XVAR
			&& file_token->type != T_PID))
	{
		parser->error = true;
		return (false);
	}
	append_redir(cmd, malloc_t_redir(rtype, file_token->token_value));
	advance_token(parser);
	return (true);
}

/*static bool	handle_operator(t_simple_cmd *cmd, t_parser *parser)
{
	t_token_node	*token;
	t_token_type	otype;

	token = get_current_token(parser);
	if (!token || (token->type != T_AND && token->type != T_OR))
		return (false);
	otype = token->type;
	append_operator(cmd, otype); // how?
	advance_token(parser);
	return (true);
}*/

t_simple_cmd	*parse_command(t_parser *parser)
{
	t_simple_cmd	*cmd;
	t_token_node	*token;
	bool			parser_flag;

	cmd = malloc_t_simple_cmd();
	if (!cmd)
		return (NULL);
	parser_flag = false;
	token = get_current_token(parser);
	while (token)
	{
		if (handle_argv(cmd, parser))
			parser_flag = true;
		else if (handle_redir(cmd, parser))
			parser_flag = true;
//		else if (handle_operator(cmd, parser)) // how?
//			parser_flag = true;
		else
			break ;
		token = get_current_token(parser);
	}
	if (!parser_flag || parser->error)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

/* Visually Summarizing the Final Data Structure
 * At the end of parsing echo hello | cat, we have a pipeline
 * 					(linked list of 2 nodes):
 *
 *    ┌─────────────────────────┐
 *    │  t_pipe_sequence (head) │
 *    ├───────────────┬─────────┘
 *    │ .cmd          ▼
 *    │  ┌───────────────────────────────────────────────┐
 *    │  │  t_simple_cmd for "echo hello"               │
 *    │  ├─────────────────────┬────────────────────────┘
 *    │  │ argv = ["echo", "hello", NULL]
 *    │  │ redirections = NULL
 *    └──►.next
 *        ┌─────────────────────────┐
 *        │ t_pipe_sequence (2nd)   │
 *        ├───────────────┬─────────┘
 *        │ .cmd          ▼
 *        │  ┌───────────────────────────────────────────┐
 *        │  │ t_simple_cmd for "cat"                   │
 *        │  ├─────────────────────┬────────────────────┘
 *        │  │ argv = ["cat", NULL]
 *        │  │ redirections = NULL
 *        └──►.next = NULL
 *
 * The first pipeline node (head) has a t_simple_cmd for ["echo", "hello"].
 * .next points to the second pipeline node, which has ["cat"].
 * .next of the second node is NULL, indicating the end of the pipeline.
 *
 * parse_command() is effectively saying:
 * 		“Read tokens until something says ‘I’m done with this command.’”
 * 
 * parse_pipeline() says:
 * 	“Keep reading commands separated by | until no more |.”
 * 
 * parse_tokens() is just the outermost layer that returns
 * 	that data structure to the rest of your program.
 *
 * Using a local t_token_type rtype = token->type; is a common,
 * legitimate approach when handling enums—particularly to save
 * the token type before you consume the token or do further logic.
 *
 */
