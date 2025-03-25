/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:58:10 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 15:47:30 by suroh            ###   ########.fr       */
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

static void	process_command_tokens(t_parser *parser, t_simple_cmd *cmd)
{
	t_token_node	*token;

	token = get_current_token(parser);
	while (token && token->type != T_PIPE && token->type != T_AND
		&& token->type != T_OR)
	{
		if (token->type == T_LESS || token->type == T_GREAT
			|| token->type == T_DLESS || token->type == T_DGREAT)
		{
			if (!process_redir_token(parser, cmd))
				return ;
		}
		else if (token->type == T_IDENTIFIER || token->type == T_VAR
			|| token->type == T_XVAR || token -> type == T_PID)
		{
			append_argv(cmd, ft_strdup(token->token_value));
			advance_token(parser);
		}
		else
			break ;
		token = get_current_token(parser);
	}
}

t_simple_cmd	*parse_command(t_parser *parser)
{
	t_simple_cmd	*cmd;

	cmd = malloc_t_simple_cmd();
	if (!cmd)
		return (NULL);
	process_command_tokens(parser, cmd);
	return (cmd);
}
