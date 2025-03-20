/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:20:39 by suroh             #+#    #+#             */
/*   Updated: 2025/03/19 19:00:05 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_export(t_almighty *mighty, char *var)
{
	if (!var)
		return ;
	if (!ft_strchr(var, '='))
		add_var(mighty->var_list, create_var(ft_strdup(var), NULL));
	else
	{
		add_var(mighty->var_list, create_var(
				ft_strndup(var, ft_strchr(var, '=') - var),
				ft_strdup(ft_strchr(var, '=') + 1)));
	}
}
