/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:14:40 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 16:29:33 by suroh            ###   ########.fr       */
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

static char	**get_path_directories(void)
{
	char	*path_env;
	char	**directories;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	directories = ft_split(path_env, ':');
	return (directories);
}

char	*find_executable(char *cmd)
{
	char	*result;
	char	**paths;

	if (is_cmd_a_path(cmd))
		return (ft_strdup(cmd));
	paths = get_path_directories();
	if (!paths)
		return (ft_strdup(cmd));
	result = search_executable(cmd, paths);
	if (!result)
		result = ft_strdup(cmd);
	free_paths(paths);
	return (result);
}
