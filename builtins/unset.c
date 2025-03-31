/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:18:36 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 20:50:17 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_unset(t_almighty *mighty, char **keys)
{
	t_var_elm	*node;
	int			i;

	mighty->exit_stat = 0;
	if (!keys)
		return ;
	i = 0;
	while (keys[i])
	{
		if (keys[i][0])
		{
			node = get_value(mighty->var_list, keys[i]);
			if (node)
				rem_var(mighty->var_list, node);
		}
		i++;
	}
}
