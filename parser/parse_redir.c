/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:24:53 by suroh             #+#    #+#             */
/*   Updated: 2025/03/13 17:36:00 by suroh            ###   ########.fr       */
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

static char	*parse_heredoc_content(char *delim)
{
	char	*line;
	char	*content;
	char	*tmp;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (true)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(content, line);
		free(content);
		content = ft_strjoin(tmp, "\n");
		free(tmp);
		free(line);
	}
	return (content);
}

static t_redir	*parse_heredoc_redir(t_parser *parser)
{
	t_redir			*redir;
	t_token_node	*token;

	advance_token(parser);
	token = get_current_token(parser);
	if (!token)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = T_DLESS;
	redir->filename = ft_strdup(token->token_value);
	advance_token(parser);
	redir->heredoc_content = parse_heredoc_content(redir->filename);
	redir->next = NULL;
	return (redir);
}

static t_redir	*parse_normal_redir(t_parser *parser)
{
	t_redir			*redir;
	t_token_node	*token;

	token = get_current_token(parser);
	if (!token)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = token->type;
	redir->filename = ft_strdup(token->token_value);
	redir->heredoc_content = NULL;
	redir->next = NULL;
	advance_token(parser);
	return (redir);
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
