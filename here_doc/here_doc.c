/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:25:13 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/05 19:56:33 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*here_doc_arr(char *hdstr, char *buff)
{
	char	*ret_str;

	buff = ft_strjoin(buff, "\n");
	ret_str = ft_strjoin(hdstr, buff);
	return (free(hdstr), free(buff), ret_str);
}

void	here_doc(t_almighty *mighty, char *eof)
{
	char	*buff;

	while (true)
	{
		buff = readline("> ");
		if (!ft_strcmp(buff, eof))
		{
			free(buff);
			break ;
		}
		mighty->here_doc_str = here_doc_arr(mighty->here_doc_str, buff);
		free(buff);
	}
}
