/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:55:54 by suroh             #+#    #+#             */
/*   Updated: 2025/03/19 13:10:32 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	validate_command_tokens(t_simple_cmd *cmd)
{
	size_t	i;

	if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (false);
	i = 0;
	while (cmd->argv[0][i])
	{
		if (!ft_isdigit(cmd->argv[0][i]))
			break ;
		i++;
	}
	if (i == ft_strlen(cmd->argv[0]))
		return (false);
	return (true);
}

/*
 * Purpose of the Loop:
 * The goal of this loop is to check whether
 * every character in cmd->argv[0] is a digit.
 *
 * The loop increments i as long as each character is a digit.
 * When it encounters a character that is not a digit,
 * it breaks out of the loop.
 * What Happens Next:
 * After the loop, the condition if (i == ft_strlen(cmd->argv[0]))
 * checks whether the loop iterated over the entire string.
 *
 * If i equals the length of the string, it means every character
 * was a digit, so the command is considered invalid (return false).
 * If i is less than the length of the string, it means
 * at least one character is not a digit, and therefore the command name
 * is acceptable (return true).
 */
