/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:20:39 by suroh             #+#    #+#             */
/*   Updated: 2025/03/28 14:09:59 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	is_valid_input(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

static void	print_export_error(char *var, t_almighty *mighty)
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

static void	parse_export_var(char *var, char **key, char **value)
{
	if (!(ft_strchr(var, '=')))
	{
		*key = ft_strdup(var);
		*value = NULL;
	}
	else
	{
		*key = ft_strndup(var, (ft_strchr(var, '=') - var));
		*value = ft_strdup((ft_strchr(var, '=') + 1));
	}
}

void	_export(t_almighty *mighty, char *var)
{
	char		*key;
	char		*value;
	t_var_elm	*node;

	if (!var)
		return ;
	if (!is_valid_input(var))
	{
		print_export_error(var, mighty);
		return ;
	}
	parse_export_var(var, &key, &value);
	node = get_value(mighty->var_list, key);
	if (node)
	{
		free(node->value);
		node->value = value;
		free(key);
	}
	else
		add_var(mighty->var_list, create_var(key, value));
}

void	builtin_export(t_almighty *mighty, char **args)
{
	int			i;
	t_var_elm	*node;

	mighty->exit_stat = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_input(args[i]))
			print_export_error(args[i], mighty);
		else if (ft_strchr(args[i], '='))
			_export(mighty, args[i]);
		else
		{
			node = get_value(mighty->var_list, args[i]);
			if (!node)
				print_export_error(args[i], mighty);
		}
		i++;
	}
}
