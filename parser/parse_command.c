/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:58:10 by suroh             #+#    #+#             */
/*   Updated: 2025/03/08 18:36:46 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	append_argv(t_simple_cmd *cmd, char *arg)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (cmd->argv[i])
		i++;
	new_argv = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = arg;
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

static void	append_redir(t_simple_cmd *cmd, t_redir *redir)
{
	t_redir	*cur;

	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		cur = cmd->redir;
		while (cur->next)
			cur = cur->next;
		cur->next = redir;
	}
}

static void	handle_redir(t_simple_cmd *command, t_parser *parser)
{
	t_token_node	*token;
	t_token_type	redir_type;
	t_redir			*redir;

	token = get_current_token(parser);
	if (token)
	{
		redir_type = token->type;
		advance_token(parser);
		token = get_current_token(parser);
		if (token)
		{
			redir = malloc_t_redir(redir_type, ft_strdup(token->token_value));
			append_redir(command, redir);
		}
		advance_token(parser);
	}
}

t_simple_cmd	*parse_command(t_parser *parser)
{
	t_simple_cmd	*command;
	t_token_node	*token;

	command = malloc_t_simple_cmd();
	if (!command)
		return (NULL);
	token = get_current_token(parser);
	while (token
		&& (token->type == T_IDENTIFIER || token->type == T_VAR
			|| token->type == T_XVAR || token->type == T_PID))
	{
		append_argv(command, ft_strdup(token->token_value));
		advance_token(parser);
		token = get_current_token(parser);
	}
	token = get_current_token(parser);
	while (token && (token->type == T_LESS || token->type == T_GREAT
			|| token->type == T_DLESS || token->type == T_DGREAT))
	{
		handle_redir(command, parser);
		token = get_current_token(parser);
	}
	return (command);
}

/*
 * t_simple_cmd	*parse_command(t_parser *parser)
 * Purpose:
 * 		Creates a simple command structure.
 * 
 * Argument Parsing:
 *		It loops while the current token is an identifier or
 *		variable type (covering normal command arguments)
 *		and appends each to the command’s argument list using append_argv.
 *
 * Redirection Parsing:
 * 		It then processes any redirection tokens (like <, >, etc.)
 * 		by calling handle_redir, which creates and
 * 		attaches redirection nodes to the command.
 *
 *
 * static void	append_argv(t_simple_cmd *cmd, char *arg)
 * Purpose:
 * 		Dynamically appends a new argument to the command’s argv array.
 * 		It allocates a new array that is one element larger,
 * 		copies over the existing arguments, appends the new argument,
 * 		and frees the old array.
 *
 * static void	handle_redir(t_simple_cmd *command, t_parser *parser)
 * Purpose:
 * 		Processes a redirection token.
 * 		Reads the redirection operator (setting its type),
 * 		advances to the next token (expected to be the file or target),
 * 		and creates a redirection node.
 * 		Calls append_redir to attach the redirection to the command.
 *
 * static void	append_redir(t_simple_cmd *cmd, t_redir *redir)
 * Purpose:
 * 		Appends a new redirection to the end of
 * 		a command’s redirection list.
 */
