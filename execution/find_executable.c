/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:14:40 by suroh             #+#    #+#             */
/*   Updated: 2025/03/18 19:58:03 by suroh            ###   ########.fr       */
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

/*
 * build_candidate:
 * 	Concatenates a directory (dir) with a "/" and
 * 		the command name (cmd) to form a candidate
 * 		full path. It frees the temporary string
 * 		after use.
 *
 *
 * search_executable:
 * 	Iterates over the array of directories (paths),
 * 		calls build_candidate for each, and uses
 * 		access() with X_OK to check if the candidate
 * 		is executable. Returns the first candidate
 * 		that works.
 *
 * get_path_directories:
 * 	Retrieves the PATH environment variable and
 * 		splits it by ':' into an array of
 * 		directory strings.
 * 	
 * find_executable:
 * 	Checks if the command already contains a '/'
 * 		(using is_cmd_a_path).
 * 	If yes, returns a duplicate of the command.
 * 	Otherwise, it gets the PATH directories,
 * 		searches for an executable using search_executable,
 * 		frees the directories array, and returns the found
 * 		candidate or a duplicate of the command if none is found.
 *
 */
