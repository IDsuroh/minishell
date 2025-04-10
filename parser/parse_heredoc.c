/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:23:53 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 23:41:43 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*parse_heredoc_content(char *delim)
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

t_redir	*parse_heredoc_redir(t_parser *parser)
{
	t_redir			*redir;
	t_token_node	*token;
	char			*delim;

	advance_token(parser);
	token = get_current_token(parser);
	if (!token)
		return (NULL);
	delim = ft_strdup(token->token_value);
	if (!delim)
		return (NULL);
	redir = malloc_t_redir(T_DLESS, delim);
	if (!redir)
	{
		free(delim);
		return (NULL);
	}
	redir->is_quote = token->processed_quote;
	advance_token(parser);
	redir->heredoc_content = parse_heredoc_content(redir->filename);
	return (redir);
}
