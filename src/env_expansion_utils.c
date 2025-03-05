/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:04:07 by suroh             #+#    #+#             */
/*   Updated: 2025/03/05 15:43:25 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_prefix(const char *str)
{
	char	*pos;

	pos = ft_strchr(str, '$');
	if (!pos)
		return (ft_strdup(str));
	return (ft_substr(str, 0, pos - str));
}

char	*get_var_name(const char *dollar_ptr)
{
	const char	*var_start;
	int			var_len;

	var_start = dollar_ptr + 1;
	if (*var_start == '$' || *var_start == '?')
		var_len = 1;
	else
	{
		var_len = 0;
		while (var_start[var_len] && (ft_isalnum(var_start[var_len])
				|| var_start[var_len] == '_'))
			var_len++;
	}
	return (ft_substr(var_start, 0, var_len));
}

char	*get_suffix(const char *dollar_ptr)
{
	const char	*var_start;
	int			var_len;

	var_start = dollar_ptr + 1;
	if (*var_start == '$' || *var_start == '?')
		var_len = 1;
	else
	{
		var_len = 0;
		while (var_start[var_len] && (ft_isalnum(var_start[var_len])
				|| var_start[var_len] == '_'))
			var_len++;
	}
	return (ft_strdup(var_start + var_len));
}

int	get_pid_from_proc(void)
{
	int		fd;
	char	buffer[64];
	int		bytes_read;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (0);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	return (ft_atoi(buffer));
}

/*
 * get_prefix:
 * Returns a duplicate of everything before the first '$' in 'str'.
 * pos - str calculates the number of characters from
 * the start of the string (str) to the first occurrence of
 * the dollar sign ('$').
 *
 * get_var_name:
 * Given a pointer to '$' in 'str', extracts the variable name.
 * Assumes variable names consist of alphanumerics and underscores.
 * For special cases ($$ or $?), the name length is 1.
 *
 * get_suffix:
 * Given a pointer to '$' in 'str',
 * extracts the suffix (text after the variable name).
 *
 * get_pid_from_proc:
 * The file /proc/self/stat begins with the current process ID
 * (PID). This code opens that file, reads its contents into
 * a buffer, and then uses ft_atoi to convert the first part
 * of the string (which is the PID) into an integer.
 * Since ft_atoi stops reading once it encounters a non-numeric
 * character (like the space after the PID), it effectively
 * extracts just the PID.
 */
