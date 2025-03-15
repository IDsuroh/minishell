/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:24:53 by suroh             #+#    #+#             */
/*   Updated: 2025/03/15 15:50:52 by suroh            ###   ########.fr       */
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

/*
 * void	append_redir(t_simple_cmd *cmd, t_redir *redir)
 * 	Purpose:
 * 		This function attaches a new redirection node (redir)
 * 		to a command’s redirection list (cmd->redir).
 * 	How it Works:
 *		If the command doesn’t have any redirections
 *		yet (cmd->redir is NULL), it sets the
 *		redirection pointer to the new node.
 *		Otherwise, it traverses the linked list until
 *		it finds the last node (where cur->next is NULL)
 *		and attaches the new node there.
 * 	Usage:
 * 		Called during parsing to build up the list of redirections
 * 		for a command.
 *
 *
 * static char	*parse_heredoc_content(char *delim)
 * 	Purpose:
 * 		This function collects the heredoc input from the user
 * 		until a line exactly matches the provided delimiter (delim).
 * 	How it Works:
 * 		It starts with an empty string (content).
 * 		It enters an infinite loop and uses readline("heredoc> ")
 * 			to prompt the user.
 * 		If readline returns NULL, it stops.
 * 		It compares the input (line) to the delimiter
 * 			using ft_strcmp:
 * 				If they match, it frees the line and breaks the loop.
 * 				If they don’t match, it appends the line to content
 * 				(first concatenating the current content with the line,
 * 				then appending a newline).
 * 		Temporary strings (tmp) are freed immediately after use.
 *	Result:
 *		Returns the complete heredoc content as
 *		a single string (with newlines).
 *
 *
 * static t_redir	*parse_heredoc_redir(t_parser *parser)
 * 	Purpose:
 * 		This function handles the parsing of a heredoc redirection.
 * 	How it Works:
 * 		Consume the Heredoc Operator:
 * 			The function calls advance_token(parser)
 * 			to skip the heredoc operator token (<<).
 * 		Get the Delimiter Token:
 * 			It then calls get_current_token(parser) to fetch
 * 			the next token, which should be the delimiter.
 * 		Allocate a Redirection Node:
 * 			It allocates a new t_redir node.
 * 		Set the Type:
 * 			It explicitly sets the type to T_DLESS.
 * 		Store the Delimiter:
 * 			The token's value (the delimiter) is duplicated
 * 			and stored in redir->filename.
 * 		Advance Token Again:
 * 			The delimiter token is then consumed
 * 			via advance_token(parser).
 * 		Collect Heredoc Content:
 * 			The function calls parse_heredoc_content(redir->filename)
 * 			using the delimiter to collect heredoc input, and stores
 * 			the result in redir->heredoc_content.
 * 		Finish Up:
 * 			It sets the next pointer to NULL and returns
 * 			the redirection node.
 * 		Usage:
 * 			This function is called when the parser encounters
 * 			a heredoc redirection operator.
 *
 *
 * static t_redir	*parse_normal_redir(t_parser *parser)
 * 	Purpose:
 * 		This function parses redirections that are
 * 		not heredocs (for example, input <, output >, or append >>).
 * 	How it Works:
 * 		It fetches the current token.
 * 		Allocates a new redirection node.
 * 		Sets the type to the token’s type.
 * 		Duplicates the token’s value into redir->filename.
 * 		Since it’s not a heredoc, redir->heredoc_content is set to NULL.
 * 		Consumes the token with advance_token(parser).
 * 		Returns the new redirection node.
 * 	Usage:
 * 		Called when the token is not T_DLESS.
 *
 *
 * t_redir	*parse_redir(t_parser *parser)
 *	This wrapper function decides which parsing function to call
 *	based on the type of the current token.
 *
 *
 *
 *
 */
