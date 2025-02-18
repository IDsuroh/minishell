/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:47:44 by suroh             #+#    #+#             */
/*   Updated: 2025/02/18 19:44:08 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	process_dquote(char *input, char *new_input, int *i)
{
	new_input[*i] = ' ';
	(*i)++;
	while (input[*i] != '"' && input[*i] != '\0')
	{
		new_input[*i] = input[*i];
		(*i)++;
	}
	if (input[*i] == '"')
	{
		new_input[*i] = ' ';
		(*i)++;
	}
}

char	*dquote_eraser(char *input)
{
	char	*new_input;
	int		i;

	new_input = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!new_input)
		return (NULL);
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '"')
			process_dquote(input, new_input, &i);
		else
		{
			new_input[i] = input[i];
			i++;
		}
	}
	new_input[i] = '\0';
	free(input);
	return (new_input);
}
