/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_flags_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:57:37 by suroh             #+#    #+#             */
/*   Updated: 2025/03/08 18:44:03 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	error_in_new_prompt(t_token_node **tmp_tokens)
{
	int	i;

	if (no_preceding_command(tmp_tokens[0]))
		return (true);
	i = 0;
	while (tmp_tokens[i])
	{
		if (tmp_tokens[i + 1] && consecutive_operators(tmp_tokens[i],
				tmp_tokens[i + 1]))
			return (true);
		i++;
	}
	return (false);
}

/*
 * Purpose:
 *
 * To validate a tokenized command (from a new prompt)
 * by checking for two specific syntax issues:
 *
 * No Preceding Command:
 * The command should not begin with an operator (e.g., pipe, &&, ||).
 *
 * Consecutive Operators:
 * Two operators should not occur in a row.
 */
