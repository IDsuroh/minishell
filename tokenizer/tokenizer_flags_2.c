/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_flags_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:01:05 by suroh             #+#    #+#             */
/*   Updated: 2025/03/05 14:12:42 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_same_char(char c1, char c2)
{
	return (c1 == c2);
}

bool	is_var(char *c)
{
	return (*(c) == '$');
}

bool	char_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

bool	is_quote_closed(char *p)
{
	char	quote;

	quote = *p;
	p++;
	while (*p && *p != quote)
		p++;
	return (*p == quote);
}
