/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_flags_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:01:05 by suroh             #+#    #+#             */
/*   Updated: 2025/02/18 20:38:12 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_same_char(char c1, char c2)
{
	return (c1 == c2);
}

bool	is_var(char *c)
{
	if (is_delimiter(*(c + 1)) || is_quote(*(c + 1))
		|| is_separator(*(c + 1)))
		return (false);
	else
		return (*(c) == '$');
}

bool	is_fake_var(char *c)
{
	if (*(c) == '$' && (is_delimiter(*(c + 1)) || is_separator(*(c + 1))))
		return (true);
	return (false);
}

bool	is_dquote(char *str)
{
	int	i;
	int	dquote_count;

	i = 0;
	dquote_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
			{
				if (str[i] == '$')
					dquote_count++;
				i++;
			}
			if (str[i] == '\0')
				dquote_count = 0;
		}
		if (str[i] != '\0')
			i++;
	}
	if (dquote_count > 0)
		return (true);
	return (false);
}

bool	char_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}
