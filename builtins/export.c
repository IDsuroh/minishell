/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:20:39 by suroh             #+#    #+#             */
/*   Updated: 2025/03/23 20:39:32 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_export(t_almighty *mighty, char *var)
{
	char		*key;
	char		*value;
	t_var_elm	*node;

	if (!var)
		return ;
	if (!ft_strchr(var, '='))
	{
		key = ft_strdup(var);
		value = NULL;
	}
	else
	{
		key = ft_strndup(var, (ft_strchr(var, '=') - var));
		value = ft_strdup(ft_strchr(var, '=') + 1);
	}
	node = get_value(mighty->var_list, key);
	if (node)
	{
		free(node->value);
		node->value = value;
		free(key);
	}
	else
		add_var(mighty->var_list, create_var(key, value));
}
