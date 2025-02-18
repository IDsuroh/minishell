/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:58:10 by suroh             #+#    #+#             */
/*   Updated: 2025/02/17 14:58:47 by suroh            ###   ########.fr       */
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
	while (*tokens
		&& ((*tokens)->type == T_IDENTIFIER || (*tokens)->type == T_VAR
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
