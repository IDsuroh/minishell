/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:40:08 by suroh             #+#    #+#             */
/*   Updated: 2024/12/29 18:11:28 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_resize_line(char **lineptr, size_t *n)
{
	char	*new_ptr;

	new_ptr = realloc(*lineptr, *n * 2);
	if (!new_ptr)
		return (-1);
	*lineptr = new_ptr;
	*n *= 2;
	return (0);
}

static int	ft_init_line(char **lineptr, size_t *n)
{
	if (!*lineptr)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}
	return (0);
}

ssize_t	ft_getline(char **lineptr, size_t *n, int fd)
{
	size_t	pos;
	ssize_t	bytes_read;
	char	c;

	pos = 0;
	if (!lineptr || !n || fd < 0 || ft_init_line(lineptr, n) == -1)
		return (-1);
	bytes_read = read(fd, &c, 1);
	while (bytes_read > 0)
	{
		if (pos + 1 >= *n && ft_resize_line(lineptr, n) == -1)
			return (-1);
		(*lineptr)[pos++] = c;
		if (c == '\n')
			break ;
		bytes_read = read(fd, &c, 1);
	}
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0 && pos == 0)
		return (0);
	(*lineptr)[pos] = '\0';
	return (pos);
}
