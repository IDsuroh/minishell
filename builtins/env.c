/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:19:49 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 18:08:40 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_env(t_almighty *mighty)
{
	char	**envp;

	mighty->exit_stat = 0;
	envp = make_envp(mighty->var_list);
	print_vars(envp);
	free_paths(envp);
}
