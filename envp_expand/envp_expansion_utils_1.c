/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:04:07 by suroh             #+#    #+#             */
/*   Updated: 2025/03/10 17:21:27 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_prefix(const char *str)
{
	char	*pos;
	char	*prefix;
	int		len;
	int		i;

	pos = ft_strchr(str, '$');
	if (!pos)
		return (ft_strdup(str));
	len = pos - str;
	prefix = (char *)malloc(sizeof(char) * (len + 1));
	if (!prefix)
		return (NULL);
	i = -1;
	while (++i < len)
		prefix[i] = str[i];
	prefix[len] = '\0';
	return (prefix);
}

char	*get_var_name(const char *dollar_ptr)
{
	const char	*var_start;

	var_start = dollar_ptr + 1;
	if (*var_start == '$' || *var_start == '?')
		return (get_special_var_name(var_start));
	else
		return (get_normal_var_name(var_start));
}

char	*get_suffix(const char *dollar_ptr)
{
	const char	*var_start;
	char		*suffix;
	int			var_len;
	int			suffix_len;
	int			i;

	var_start = dollar_ptr + 1;
	if (*var_start == '$' || *var_start == '?')
		var_len = 1;
	else
		var_len = get_var_len(var_start);
	suffix_len = 0;
	while (var_start[var_len + suffix_len])
		suffix_len++;
	suffix = (char *)malloc(sizeof(char) * (suffix_len + 1));
	if (!suffix)
		return (NULL);
	i = -1;
	while (++i < suffix_len)
		suffix[i] = var_start[var_len + i];
	suffix[i] = '\0';
	return (suffix);
}

char	*extract_pid_from_stat(const char *stat_str)
{
	int		len;
	int		i;
	char	*pid_str;

	len = 0;
	while (stat_str[len] && stat_str[len] != ' ')
		len++;
	pid_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!pid_str)
		return (NULL);
	i = -1;
	while (++i < len)
		pid_str[i] = stat_str[i];
	pid_str[len] = '\0';
	return (pid_str);
}

char	*get_pid_from_proc(void)
{
	int		fd;
	char	buffer[64];
	int		bytes_read;
	char	*pid_str;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (0);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
	{
		close(fd);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	pid_str = extract_pid_from_stat(buffer);
	return (pid_str);
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
