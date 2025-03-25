/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:24:53 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 15:47:06 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	append_redir(t_simple_cmd *cmd, t_redir *redir)
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

t_redir	*parse_redir(t_parser *parser)
{
	t_token_node	*token;

	token = get_current_token(parser);
	if (!token)
		return (NULL);
	if (token->type == T_DLESS)
		return (parse_heredoc_redir(parser));
	else
		return (parse_normal_redir(parser));
}

bool	process_redir_token(t_parser *parser, t_simple_cmd *cmd)
{
	t_redir	*redir;

	redir = parse_redir(parser);
	if (redir)
		append_redir(cmd, redir);
	else
		return (false);
	return (true);
}
