/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_counters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:48:04 by suroh             #+#    #+#             */
/*   Updated: 2025/03/05 13:44:12 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	quote_counter(char **input)
{
	char	quote;

	quote = **input;
	(*input)++;
	while (**input && **input != quote)
		(*input)++;
	if (**input == quote)
		(*input)++;
}

static void	separator_counter(char **input)
{
	if ((*input)[1] && (*input)[0] == (*input)[1])
		(*input) += 2;
	else
		(*input) += 1;
}

static void	var_counter(char **input)
{
	(*input)++;
	if (**input == '?' || **input == '$')
		(*input)++;
	else
	{
		while (**input && !is_separator(**input)
			&& !is_delimiter(**input) && **input != '$')
		{
			if ((**input == '\'' || **input == '\"')
				&& is_quote_closed(*input))
				break ;
			(*input)++;
		}
	}
}

static void	string_counter(char **input)
{
	(*input)++;
	while (**input && !is_delimiter(**input) && !is_var(*input)
		&& !is_separator(**input) && !is_quote(**input))
		(*input)++;
}

int	count_tokens(char *input)
{
	int	count;

	count = 0;
	while (*input)
	{
		if ((is_quote(*input) && is_quote_closed(input))
			|| (is_var_squote(input) || is_var_dquote(input)))
			quote_counter(&input);
		else if (is_separator(*input))
			separator_counter(&input);
		else if (is_var(input))
			var_counter(&input);
		else if (is_delimiter(*input))
			input++;
		else
			string_counter(&input);
		count++;
	}
	return (count);
}
