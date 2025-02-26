/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage_logic_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:20:01 by suroh             #+#    #+#             */
/*   Updated: 2025/02/26 22:37:53 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_short_var(char **token_end, int *i)
{
	if (**token_end == '?' || **token_end == '$')
	{
		(*token_end)++;
		*i = 2;
	}
}

void	handle_normal_var(char **token_end, int *i)
{
	while (**token_end && !is_separator(**token_end)
		&& !is_delimiter(**token_end) && **token_end != '$')
	{
		if ((**token_end == '\'' || **token_end == '\"')
			&& is_quote_closed(*token_end))
			break ;
		(*token_end)++;
		(*i)++;
	}
}
