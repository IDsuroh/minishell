/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:18:36 by suroh             #+#    #+#             */
/*   Updated: 2025/03/23 20:09:31 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_unset(t_almighty *mighty, char *key)
{
	t_var_elm	*node;

	if (!key)
		return ;
	node = get_value(mighty->var_list, key);
	if (node)
		rem_var(mighty->var_list, node);
}
