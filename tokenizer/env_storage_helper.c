/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_storage_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 23:03:57 by suroh             #+#    #+#             */
/*   Updated: 2025/01/15 20:32:44 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*tmp_fake_var(char *token_start, char **token_end)
{
	char	*tmp;
	int		i;

	if (!token_start || !*token_end)
		return (NULL);
	i = 0;
	while (**token_end && !is_separator(**token_end))
	{
		(*token_end)++;
		i++;
	}
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, token_start, i + 1);
	return (tmp);
}

int	fake_var_len(char *tmp)
{
	int		i;
	int		count;
	bool	flag;

	flag = false;
	count = 0;
	i = 0;
	while (tmp[i])
	{
		if (is_delimiter(tmp[i]))
		{
			flag = true;
			i++;
		}
		else
		{
			if (flag)
				count++;
			flag = false;
			count++;
			i++;
		}
	}
	return (count);
}

char	*epur_fake_var(char *token, char *tmp)
{
	int		j;
	bool	flag;

	j = 0;
	flag = false;
	while (*tmp)
	{
		if (is_delimiter(*tmp))
		{
			flag = true;
			tmp++;
		}
		else
		{
			if (flag)
			{
				token[j++] = ' ';
				flag = false;
			}
			token[j++] = *tmp++;
		}
	}
	token[j] = '\0';
	return (token);
}
