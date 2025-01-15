/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_counters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:48:04 by suroh             #+#    #+#             */
/*   Updated: 2025/01/14 21:06:24 by suroh            ###   ########.fr       */
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
