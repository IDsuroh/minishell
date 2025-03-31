/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:14:40 by suroh             #+#    #+#             */
/*   Updated: 2025/03/31 01:08:32 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*build_candidate(char *dir, char *cmd)
{
	char	*temp;
	char	*candidate;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	candidate = ft_strjoin(temp, cmd);
	free(temp);
	return (candidate);
}

static char	*search_executable(char *cmd, char **paths)
{
	int		i;
	char	*candidate;
	char	*result;

	i = 0;
	result = NULL;
	while (paths[i])
	{
		candidate = build_candidate(paths[i], cmd);
		if (!candidate)
			break ;
		if (access(candidate, X_OK) == 0)
		{
			result = candidate;
			break ;
		}
		free(candidate);
		i++;
	}
	return (result);
}

static char	*get_env(const char *name, t_list_header *var_list)
{
	t_var_elm	*curr;

	if (!var_list)
		return (NULL);
	curr = var_list->head;
	while (curr)
	{
		if (ft_strcmp(curr->key, name) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

static char	**get_path_directories(t_almighty *mighty)
{
	char	*path_env;
	char	**directories;

	path_env = get_env("PATH", mighty->var_list);
	if (!path_env || path_env[0] == '\0')
		return (NULL);
	directories = ft_split(path_env, ':');
	return (directories);
}

char	*find_executable(char *cmd, t_almighty *mighty)
{
	char	*result;
	char	**paths;

	if (is_cmd_a_path(cmd))
		return (ft_strdup(cmd));
	paths = get_path_directories(mighty);
	if (!paths)
		return (NULL);
	result = search_executable(cmd, paths);
	free_paths(paths);
	return (result);
}
