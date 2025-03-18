/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_flags_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:20:03 by suroh             #+#    #+#             */
/*   Updated: 2025/03/18 19:31:46 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	no_preceding_command(t_token_node *token)
{
	if (token
		&& (token->type == T_PIPE || token->type == T_AND
			|| token->type == T_OR))
	{
		printf("minishell: syntax error near unexpected token `%s'\n\n",
			(*token).token_value);
		return (true);
	}
	return (false);
}

bool	consecutive_operators(t_token_node *token, t_token_node *next)
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
			printf("minishell: syntax error near unexpected token `%s'\n\n",
				(*next).token_value);
			return (true);
		}
	}
	return (false);
}

bool	incomplete_input(t_token_node *token, bool *op_open)
{
	if (token
		&& (token->type == T_PIPE || token->type == T_AND
			|| token->type == T_OR))
	{
		*op_open = true;
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

bool	validate_command_tokens(t_token_node **tokens)
{
	if (tokens[0]->type == T_PID || tokens[0]->type == T_XVAR
		|| tokens[0]->type == T_VAR)
	{
		printf("%s: command not found\n", tokens[0]->token_value);
		return (false);
	}
	return (true);
}

/*
 * bool	no_preceding_command(t_token_node *token)
 * Purpose:
 * 		Checks if the very first token in the input is an operator
 * 		that should come between commands
 * 		(such as a pipe |, logical AND &&, or logical OR ||).
 *
 * What It Does:
 * 		If the token exists and its type is one of these operators,
 * 		it prints a syntax error message indicating an unexpected token.
 * 		Returns true to indicate an error. Otherwise, it returns false.
 *
 * bool	consecutive_operators(t_token_node *token, t_token_node *next)
 * Purpose:
 * 		Ensures that two operator tokens do not appear consecutively
 * 		in the input.
 *
 * What It Does:
 * 		Checks if the current token is an operator (covering pipes,
 * 		logical operators, and redirection operators). If the next token is
 * 		also an operator, it prints a syntax error message using
 * 		the second operator’s value.
 * 		Returns true if such a syntax error is found; otherwise,
 * 		it returns false.
 *
 * bool	incomplete_input(t_token_node *token, bool *op_open)
 * Purpose:
 *		Checks whether the last token in the input is an operator
 *		that suggests the command is incomplete
 *		(for example, a trailing pipe or logical operator).
 *
 * What It Does:
 * 		If the token exists and is one of the operators
 * 		(|, &&, or ||), it sets the flag op_open to true
 * 		indicating an open (incomplete) operator.
 * 		Returns true to signal that the input is incomplete.
 * 		Otherwise, returns false.
 * 
 * ***Only for open inputs.
 * bool	error_prompt(t_token_node **tokens, bool *op_open)
 * Purpose:
 * 		Orchestrates the overall syntax checking by using
 * 		the above helper functions.
 *
 * What It Does:
 * 	
 * 	Check the First Token:
 * 		Uses no_preceding_command to verify that the input
 * 		doesn’t start with an operator.
 *
 * 	Check for Consecutive Operators:
 * 		Iterates through the tokens and, for each pair of
 * 		consecutive tokens, uses consecutive_operators to
 * 		ensure that two operators don’t appear back-to-back.
 *
 * 	Check the Last Token:
 * 		After processing all tokens, it checks the final token
 * 		using incomplete_input to see if the command ends with
 * 		an operator, which would indicate an incomplete input.
 *
 * 	Error Reporting:
 * 		If any of these checks return true, an error has been
 * 		detected and the function returns true overall.
 * 		Otherwise, it returns false meaning the token stream
 * 		passed these syntax checks.
 */
