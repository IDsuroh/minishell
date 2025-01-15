/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_flags_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:01:05 by suroh             #+#    #+#             */
/*   Updated: 2025/01/14 21:14:49 by suroh            ###   ########.fr       */
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
	if (*(c) == '$' && (is_delimiter(*(c + 1)) || is_quote(*(c + 1))
			|| is_separator(*(c + 1))))
		return (true);
	return (false);
}
