/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:42:03 by miteixei          #+#    #+#             */
/*   Updated: 2025/01/06 22:32:05 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// To handle environment variables it is necessary to initialize an address
//   with a copy of all variables provided to the program at startup,
//   and then each time one wants to add, modify, or remove a variable
//   a copy of the double char pointer is to be created.

void	copy_vars(const char **envp, char ***var_struct)
{
	size_t	env_size;
	size_t	i;

	env_size = 0;
	while (envp[env_size])
		++env_size;
	*var_struct = malloc((env_size + 1) sizeof(char **));
	i = 0;
	while (env_size > i++)
		*var_struct[i - 1] = ft_strdup(envp[i - 1]);
}

void	rem_var(char *arg, const char **env_struct);
void	add_var(char *arg, char ***env_struct);

void	_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		ft_putstr_fd(envp[i++], 1)
}
