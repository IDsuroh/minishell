/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:58:10 by suroh             #+#    #+#             */
/*   Updated: 2025/02/24 23:46:31 by suroh            ###   ########.fr       */
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
