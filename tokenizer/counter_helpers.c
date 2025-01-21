/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:03:10 by suroh             #+#    #+#             */
/*   Updated: 2025/01/16 17:41:11 by suroh            ###   ########.fr       */
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

//Each functions are called by the count_tokens function in tokenizer_counters.c
//
//quote_counter:	quote_counter(&input, &count);
//	- Counts the number of quotes in the input string.
//	- The function increments the input pointer until it reaches
//		the closing quote.
//	- After, the function increments the count.
//
//separator_counter:	separator_counter(&input, &count);
//	- Counts the number of separators in the input string.
//	- The function increments the input pointer by 2 if
//		the next character is the same.
//	- If not, the function increments the input pointer by 1.
//	- After, the function increments the count.
//
//var_counter:	var_counter(&input, &count);
//	- Counts the number of variables in the input string.
//	- The function increments the input pointer until it reaches
//		the end of the variable.
//	- If the variable is a special variable, the function
//		increments the input pointer.
//	- If the variable is just a string, the function increments
//		the input pointer until it reaches '\0',
//		any delimiter (' ', '\n', '\t'), or a separator.
//	- After, the function increments the count.
//
//string_counter:	string_counter(&input, &count);
//	- Counts the number of strings in the input string.
//
//fake_var_counter:	fake_var_counter(&input, &count);
//	- Counts the number of fake variables in the input string.
//	- The function increments the input pointer until it reaches
//		a separator or '\0'.
//	- After, the function increments the count.
//	- The term fake variable is just a categorization which signifies
//		any string which starts with the '$' symbol but has
//		multiple or single whitespaces in between the '$' and
//		the characters.
//
//next file to read: go back to: tokenizer.c
