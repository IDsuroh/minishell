/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_normal_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:07:44 by suroh             #+#    #+#             */
/*   Updated: 2025/03/26 18:42:30 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*parse_redir_filename(t_parser *parser)
{
	char			*filename;
	int				skip;
	t_token_node	*token;

	skip = 1;
	token = get_current_token(parser);
	if (!token)
		return (NULL);
	if (token->type == T_DGREAT || token->type == T_DLESS)
		skip = 2;
	filename = ft_strtrim(token->token_value + skip, " \t");
	if (ft_strlen(filename) > 0)
	{
		advance_token(parser);
		return (filename);
	}
	free(filename);
	advance_token(parser);
	token = get_current_token(parser);
	if (!token)
		return (NULL);
	filename = ft_strtrim(token->token_value, " \t");
	advance_token(parser);
	return (filename);
}

t_redir	*parse_normal_redir(t_parser *parser)
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
	redir->next = NULL;
	redir->filename = parse_redir_filename(parser);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	redir->heredoc_content = NULL;
	return (redir);
}
