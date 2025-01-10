/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:42:03 by miteixei          #+#    #+#             */
/*   Updated: 2025/01/10 19:46:06 by miteixei         ###   ########.fr       */
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
	*var_struct = malloc((env_size + 1) * sizeof(char **));
	i = 0;
	while (env_size > i++)
		*var_struct[i - 1] = ft_strdup(envp[i - 1]);
	*var_struct[env_size] = NULL;
}

bool	var_exists(char *arg, char **var_list)
{
	while (*var_list)
	{
		if (!ft_strcmp(*var_list, arg) && *var_list[ft_strlen(arg)] == '=')
			return (true);
		++var_list;
	}
	return (false);
}

void	rem_var(char *arg, char ***var_struct)
{
	char	**old_var;
	char	**new_var;
	size_t	i;

	if (!var_exists(arg, var_struct))
		return ;
	old_var = *var_struct;
	new_var = old_var;
	while (*(new_var++))
		;
	new_var = malloc((new_var - old_var) * sizeof(char **));
	i = 0;
	while (*old_var)
	{
		if (ft_strcmp(*old_var, arg) && *old_var[ft_strlen(arg)] == '=')
			new_var[i++] = ft_strdup(*old_var);
		++old_var;
	}
	new_var[i] = NULL;
	while (*var_struct)
		free(*((*var_struct)++));
	free(*var_struct);
	*var_struct = new_var;
}

void	add_var(char *arg, char ***env_struct)
{
	
}

void	_env(char **envp)
{
	while (*envp)
		ft_putstr_fd(*(envp++), 1);
}
