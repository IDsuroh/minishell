/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:02:38 by suroh             #+#    #+#             */
/*   Updated: 2025/02/11 19:45:18 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	no_preceding_command(t_token_node *token)
{
	if (token
		&& (token->type == T_PIPE || token->type == T_AND
			|| token->type == T_OR || token->type == T_GREAT
			|| token->type == T_DGREAT || token->type == T_LESS
			|| token->type == T_DLESS))
	{
		printf("minishell: syntax error near unexpected token `%s'",
			(*token).token_value);
		return (true);
	}
	return (false);
}

static bool	consecutive_operators(t_token_node *token, t_token_node *next)
{
	if (token
		&& (token->type == T_PIPE || token->type == T_AND
			|| token->type == T_OR || token->type == T_GREAT
			|| token->type == T_DGREAT || token->type == T_LESS
			|| token->type == T_DLESS))
	{
		if (next
			&& (next->type == T_PIPE || next->type == T_AND
				|| next->type == T_OR || next->type == T_GREAT
				|| next->type == T_DGREAT || next->type == T_LESS
				|| next->type == T_DLESS))
		{
			printf("minishell: syntax error near unexpected token `%s'",
				(*next).token_value);
			return (true);
		}
	}
	return (false);
}

static bool	incomplete_input(t_token_node *token, bool *op_open)
{
	if (token
		&& (token->type == T_PIPE || token->type == T_AND
			|| token->type == T_OR))
	{
		*op_open = true;
		return (true);
	}
	else if (token
		&& (token->type == T_GREAT || token->type == T_DGREAT
			|| token->type == T_LESS
			|| token->type == T_DLESS))
	{
		printf("bash: syntax error near unexpected token `newline'");
		return (true);
	}
	return (false);
}

bool	error_prompt(t_token_node **tokens, bool *op_open)
{
	int	i;

	if (no_preceding_command(tokens[0]))
		return (true);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i + 1] && consecutive_operators(tokens[i], tokens[i + 1]))
			return (true);
		i++;
	}
	i--;
	if (incomplete_input(tokens[i], op_open))
		return (true);
	return (false);
}
