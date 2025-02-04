/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:28:53 by suroh             #+#    #+#             */
/*   Updated: 2025/02/04 22:15:52 by suroh            ###   ########.fr       */
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
	append_argv(cmd, token->token_value);
	advance_token(parser);
	return (true);
}

static bool	handle_redir(t_simple_cmd *cmd, t_parser *parser)
{
	t_token_node	*token;
	t_token_node	*file_token;
	t_token_type	rtype;
	t_redir			*redir;

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
		parser->redir_error = true;
		return (false);
	}
	redir = malloc_t_redir(rtype, file_token->token_value);
	append_redir(cmd, redir);
	advance_token(parser);
	return (true);
}

t_simple_cmd	*parse_command(t_parser *parser)
{
	t_simple_cmd	*cmd;
	t_token_node	*token;

	cmd = malloc_t_simple_cmd();
	if (!cmd)
		return (NULL);
	token = get_current_token(parser);
	while (token)
	{
		if (handle_argv(cmd, parser))
			;
		else if (handle_redir(cmd, parser))
			;
		else
			break ;
		token = get_current_token(parser);
	}
	return (cmd);
}
