/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:03:10 by suroh             #+#    #+#             */
/*   Updated: 2025/01/15 00:46:16 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	quote_counter(char **input, int *count)
{
	char	quote;

	quote = **input;
	(*input)++;
	while (**input && **input != quote)
		(*input)++;
	if (**input == quote)
	{
		(*input)++;
		(*count)++;
	}
	else if (**input == '\0')
		(*count)++;
}

void	separator_counter(char **input, int *count)
{
	(*count)++;
	if ((*input)[1] && (*input)[0] == (*input)[1])
		(*input) += 2;
	else
		(*input) += 1;
}

void	var_counter(char **input, int *count)
{
	(*input)++;
	if (**input == '?')
		(*input)++;
	else if (**input == '$')
		(*input)++;
	else
	{
		while (**input && !is_separator(**input)
			&& !is_delimiter(**input))
			(*input)++;
	}
	(*count)++;
}

void	string_counter(char **input, int *count)
{
	(*input)++;
	while (**input && !is_delimiter(**input) && !is_var(*input)
		&& !is_separator(**input) && !is_quote(**input))
		(*input)++;
	(*count)++;
}

void	fake_var_counter(char **input, int *count)
{
	(*input)++;
	while (**input && !is_separator(**input))
		(*input)++;
	(*count)++;
}
