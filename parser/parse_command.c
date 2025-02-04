/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:58:10 by suroh             #+#    #+#             */
/*   Updated: 2025/02/03 20:05:02 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_redir(t_simple_cmd *command, t_token_node **tokens,
			t_parser *parser)
{
	t_token_type	redir_type;
	t_redir			*redir;

	if (*tokens)
	{
		redir_type = (*tokens)->type;
		advance_token(parser);
		(*tokens) = get_current_token(parser);
		if (*tokens)
		{
			redir = malloc_t_redir(redir_type, (*tokens)->token_value);
			append_redir(command, redir);
		}
		advance_token(parser);
	}
}

t_simple_cmd	*parse_command(t_parser *parser, t_token_node **tokens)
{
	t_simple_cmd	*command;

	command = malloc_t_simple_cmd();
	if (!command)
		return (NULL);
	while (*tokens && ((*tokens)->type == T_IDENTIFIER || (*tokens)->type == T_VAR
			|| (*tokens)->type == T_XVAR || (*tokens)->type == T_PID))
	{
		append_argv(command, (*tokens)->token_value);
		advance_token(parser);
		*tokens = get_current_token(parser);
	}
	while (*tokens && ((*tokens)->type == T_LESS || (*tokens)->type == T_GREAT
			|| (*tokens)->type == T_DLESS || (*tokens)->type == T_DGREAT))
	{
		handle_redir(command, tokens, parser);
		*tokens = get_current_token(parser);
	}
	return (command);
}
