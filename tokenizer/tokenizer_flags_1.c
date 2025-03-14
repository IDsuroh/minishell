/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_flags_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:15:12 by suroh             #+#    #+#             */
/*   Updated: 2025/02/25 16:51:45 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	is_separator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&');
}

bool	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_string(char c)
{
	return (!is_quote(c) && !is_separator(c) && !is_delimiter(c));
}

bool	is_whitespace(char *input)
{
	if (!input)
		return (true);
	while (*input)
	{
		if (!is_delimiter(*input))
			return (false);
		input++;
	}
	return (true);
}
