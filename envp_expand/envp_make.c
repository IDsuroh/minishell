/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_make.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:26:24 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 17:30:22 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_exported_env(t_list_header *header)
{
	t_var_elm	*elm;
	int			count;

	count = 0;
	elm = header->head;
	while (elm)
	{
		if (elm->exported && elm->value != NULL)
			count++;
		elm = elm->next;
	}
	return (count);
}

static char	*build_env_string(t_var_elm *elm)
{
	int		len_key;
	int		len_value;
	char	*str;

	len_key = ft_strlen(elm->key);
	len_value = ft_strlen(elm->value);
	str = malloc(len_key + 1 + len_value + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, elm->key, len_key + 1);
	ft_strlcpy(str + len_key, "=", 2);
	ft_strlcpy(str + len_key + 1, elm->value, len_value + 1);
	return (str);
}

static char	**fill_envp_array(t_list_header *header, int count)
{
	t_var_elm	*elm;
	char		**envp;
	int			i;

	envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	elm = header->head;
	while (elm)
	{
		if (elm->exported && elm->value != NULL)
		{
			envp[i] = build_env_string(elm);
			if (!envp[i])
			{
				free_envp_array(envp, i);
				return (NULL);
			}
			i++;
		}
		elm = elm->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**make_envp(t_list_header *header)
{
	char	**envp;
	int		count;

	count = count_exported_env(header);
	envp = fill_envp_array(header, count);
	return (envp);
}
