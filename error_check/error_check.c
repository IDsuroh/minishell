/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:02:38 by suroh             #+#    #+#             */
/*   Updated: 2025/02/05 21:40:04 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	no_preceding_command(t_token_node *token)
{
	if (((*token).type == T_PIPE || (*token).type == T_AND
			|| (*token).type == T_OR || (*token).type == T_GREAT
			|| (*token).type == T_DGREAT || (*token).type == T_LESS
			|| (*token).type == T_DLESS))
	{
		printf("minishell: syntax error near unexpected token `%s'",
			(*token).token_value);
		return (true);
	}
	return (false);
}

static bool	consecutive_operators(t_token_node *token)
{
	t_token_node	*next;

	next = token + 1;
	if ((*token).type == (*next).type)
		return (true);
	if (((*token).type == T_PIPE || (*token).type == T_AND
			|| (*token).type == T_OR || (*token).type == T_GREAT
			|| (*token).type == T_DGREAT || (*token).type == T_LESS
			|| (*token).type == T_DLESS))
	{
		if (((*token).type == T_PIPE || (*token).type == T_AND
				|| (*token).type == T_OR || (*token).type == T_GREAT
				|| (*token).type == T_DGREAT || (*token).type == T_LESS
				|| (*token).type == T_DLESS))
			return (true);
	}
	return (false);
}

static bool	incomplete_input(t_token_node *token)
{
	if (((*token).type == T_PIPE || (*token).type == T_AND
			|| (*token).type == T_OR))
	{
//		trigger_prompt();
		return (true);
	}
	else if (((*token).type == T_GREAT || (*token).type == T_DGREAT
			|| (*token).type == T_LESS
			|| (*token).type == T_DLESS))
	{
		printf("bash: syntax error near unexpected token `newline'");
		return (true);
	}
	return (false);
}

bool	exists_error(t_token_node **tokens)
{
	t_token_node	**tmp;
	int				i;

	tmp = tokens;
	if (no_preceding_command(tmp[0]))
		return (true);
	i = 0;
	while (tmp && tmp[i])
	{
		if (consecutive_operators(tmp[i]))
			return (true);
		i++;
	}
	if (incomplete_input(tmp[i]))
		return (true);
	return (false);
}

/*
 * ***********Correct errors first
 *
 * 1. fix main.c
 * 
 * 2.
 *
 * static bool	incomplete_input(t_token_node *token)
 * {
 *	if (((*token).type == T_PIPE || (*token).type == T_AND
 *			|| (*token).type == T_OR))
 *	{
 *		trigger_prompt(); <------------- 	****Make logic****
 *		return (true);
 *	}
 *	else if (((*token).type == T_GREAT || (*token).type == T_DGREAT
 *			|| (*token).type == T_LESS
 *			|| (*token).type == T_DLESS))
 *	{
 *		printf("bash: syntax error near unexpected token `newline'");
 *		return (true);
 *	}
 * }
 *
 * 3. need to simulate:
 *
 *	pipe>
 *	
 *	cmdor>
 *	
 *	cmdand>
 *
 */
