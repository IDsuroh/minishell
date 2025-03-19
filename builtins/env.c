/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:19:49 by suroh             #+#    #+#             */
/*   Updated: 2025/03/19 18:50:41 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_env(t_almighty *mighty)
{
	char	**envp;

	envp = make_envp(mighty->var_list);
	print_vars(envp);
	free_paths(envp);
}
