/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:20:39 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 20:39:17 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_identifier(const char *str)
{
	int		len;
	char	*id;

	if (ft_strchr(str, '='))
		len = ft_strchr(str, '=') - str;
	else
		len = ft_strlen(str);
	id = ft_strndup(str, len);
	return (id);
}

bool	is_valid_input(char *str)
{
	int		i;
	char	*id;

	if (!str || !str[0])
		return (false);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (false);
	id = get_identifier(str);
	if (!id)
		return (false);
	free(id);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

void	print_export_error(char *var, t_almighty *mighty)
{
	char	*pre;
	char	*suf;

	pre = "minishell: export: `";
	suf = "': not a valid identifier\n";
	write(STDERR_FILENO, pre, ft_strlen(pre));
	write(STDERR_FILENO, var, ft_strlen(var));
	write(STDERR_FILENO, suf, ft_strlen(suf));
	mighty->exit_stat = 1;
}

void	parse_export_var(char *var, char **key, char **value)
{
	char	*equal_ptr;

	equal_ptr = ft_strchr(var, '=');
	if (!equal_ptr)
	{
		*key = ft_strdup(var);
		*value = NULL;
	}
	else
	{
		*key = ft_strndup(var, equal_ptr - var);
		if (ft_strlen(equal_ptr + 1) == 0)
			*value = ft_strdup("");
		else
			*value = ft_strdup(equal_ptr + 1);
	}
}
