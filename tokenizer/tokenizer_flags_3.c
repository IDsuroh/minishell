/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_flags_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:27:23 by suroh             #+#    #+#             */
/*   Updated: 2025/02/26 22:18:13 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_var_dquote(char *str)
{
	int	i;
	int	var_count;

	i = 0;
	var_count = 0;
	if (str[i] != '\"')
		return (false);
	i++;
	while (str[i] != '\0' && str[i] != '\"')
	{
		if (str[i] == '$')
			var_count++;
		i++;
	}
	if (str[i] == '\0')
		var_count = 0;
	if (var_count > 0 && str[i] == '\"')
		return (true);
	return (false);
}

bool	is_var_squote(char *str)
{
	int	i;
	int	var_count;

	i = 0;
	var_count = 0;
	if (str[i] != '\'')
		return (false);
	i++;
	while (str[i] != '\0' && str[i] != '\'')
	{
		if (str[i] == '$')
			var_count++;
		i++;
	}
	if (str[i] == '\0')
		var_count = 0;
	if (var_count > 0 && str[i] == '\'')
		return (true);
	return (false);
}
