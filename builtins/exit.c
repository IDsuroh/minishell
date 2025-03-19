/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:10:17 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/19 17:54:02 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_exit_(t_almighty *mighty, int *var_exit)
{
	int	exit_val;

	if (var_exit)
		exit_val = *var_exit;
	else
		exit_val = mighty->exit_stat;
	// FREE EVERYTHING
	free_all(mighty);
	free(mighty);
	exit(exit_val);
}

// no need to add anything but
// any allocated memory that has been made and
// is still accessible in the execution process
// needs to be referenced in almighty. (when executing exit)
