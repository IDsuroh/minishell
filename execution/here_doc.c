/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:25:13 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/10 19:46:39 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*heredoc_arr(char *hdstr, char *buff)
{
	char	*ret_str;

	buff = ft_strjoin(buff, "\n");
	ret_str = ft_strjoin(hdstr, buff);
	return (free(hdstr), free(buff), ret_str);
}

// The here-doc is a pseudo text file streamed into the stdin of a command.
// I'm simply putting it into a string
//   separated by newlines as new lines come in.
void	heredoc(const char *eof, t_almighty *mighty)
{
	char	*buff;

	while (true)
	{
		buff = readline("heredoc> ");
		if (!ft_strcmp(buff, eof))
		{
			free(buff);
			break ;
		}
		mighty->here_doc_str = heredoc_arr(mighty->here_doc_str, buff);
		free(buff);
	}
}
