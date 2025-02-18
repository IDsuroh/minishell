/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_counters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:48:04 by suroh             #+#    #+#             */
/*   Updated: 2025/02/18 19:04:45 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		else if (is_var(input))
			var_counter(&input, &count);
		else if (is_fake_var(input))
			fake_var_counter(&input, &count);
		else if (is_delimiter(*input))
			input++;
		else
			string_counter(&input, &count);
	}
	return (count);
}

//The count tokens function counts the number of tokens in the input string.
//The purpose of counting beforehand is to utilize the count of tokens to
//iterate though the input string and store the tokens in an array of strings,
//which will help the function ft_strtok_r go through the input.
//The function returns the number of tokens which are categorized by the flags.
//
//quotes: ', "
//separators: |, >, <, &
//variables: $
//fake variables: $(with whitespaces)
//delimiters: whitespaces, tabs, newlines
//
//next file to read: counter_helpers.c
