/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_counters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:48:04 by suroh             #+#    #+#             */
/*   Updated: 2025/01/13 18:16:13 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	quote_counter(char **input, int *count)
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

static void	separator_counter(char **input, int *count)
{
	(*count)++;
	if ((*input)[1] && (*input)[0] == (*input)[1])
		(*input) += 2;
	else
		(*input) += 1;
}

static void	string_counter(char **input, int *count)
{
	while (**input && !is_separator(**input) && !is_quote(**input)
		&& !is_delimiter(**input))
		(*input)++;
	(*count)++;
}

int	count_tokens(char *input)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (is_quote(*input))
			quote_counter(&input, &count);
		else if (is_separator(*input))
			separator_counter(&input, &count);
		else if (is_delimiter(*input))
			input++;
		else
			string_counter(&input, &count);
	}
	return (count);
}
