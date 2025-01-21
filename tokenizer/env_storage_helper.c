/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_storage_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 23:03:57 by suroh             #+#    #+#             */
/*   Updated: 2025/01/16 17:34:25 by suroh            ###   ########.fr       */
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

//The file is solely dedicated to the storage of fake variables.
//The fake variables are stored in a different way than the regular variables.
//
//tmp_fake_var:	tmp_fake_var(token_start, &token_end)
//	- Store the fake variable in a temporary string.
//	- The function increments the token_end pointer until it reaches the end
//		or a separator.
//	- Then the content of the input is copied to the tmp string.
//	- The function returns the temporary string.
//
//fake_var_len:	fake_var_len(tmp)
//	- Count the length of the fake variable which means that any whitespaces
//		after the first character; (input[0], or '$') and in between
//		contents will be shortened to just one space and will be counted
//		as one character.
//	- Of course, the other characters will be counted as one character.
//	- The function returns the count.
//
//epur_fake_var:	epur_fake_var(token, tmp)
//	- The function copies the contents of the tmp string to the token string.
//	- The function removes any extra whitespaces in between the contents.
//	- The function utilized the logic of epur_str which was one of the test
//		questions of exam 2.
//
//next file to read: go back to: storage_logic.c:
//			to check the fake variable storage logic.
//or: go back to: tokenizer.c:
