/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:09:46 by suroh             #+#    #+#             */
/*   Updated: 2025/01/30 18:50:27 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_node	*get_current_token(t_parser *parser)
{
	if (parser->tokens[parser->cur_idx] == NULL)
		return (NULL);
	return (parser->tokens[parser->cur_idx]);
}

t_token_node	*get_next_token(t_parser *parser)
{
	if (parser->tokens[parser->cur_idx + 1] == NULL)
		return (NULL);
	return (parser->tokens[parser->cur_idx + 1]);
}

t_token_node	*get_prev_token(t_parser *parser)
{
	if (parser->cur_idx == 0)
		return (NULL);
	return (parser->tokens[parser->cur_idx - 1]);
}

void	advance_token(t_parser *parser)
{
	if (parser->tokens[parser->cur_idx] != NULL)
		parser->cur_idx++;
}
