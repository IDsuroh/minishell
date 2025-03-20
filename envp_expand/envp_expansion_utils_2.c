/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_expansion_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:23:59 by suroh             #+#    #+#             */
/*   Updated: 2025/03/20 22:33:24 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_var_len(const char *var_start)
{
	int	var_len;

	var_len = 0;
	while (var_start[var_len] && (ft_isalnum(var_start[var_len])
			|| var_start[var_len] == '_'))
		var_len++;
	return (var_len);
}

char	*get_special_var_name(const char *var_start)
{
	char	*var_name;

	var_name = (char *)malloc(sizeof(char) * 2);
	if (!var_name)
		return (NULL);
	var_name[0] = *var_start;
	var_name[1] = '\0';
	return (var_name);
}

char	*get_normal_var_name(const char *var_start)
{
	int		var_len;
	char	*var_name;
	int		i;

	var_len = get_var_len(var_start);
	var_name = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < var_len)
	{
		var_name[i] = var_start[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*strip_var_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\"' && str[len - 1] == '\"')
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
