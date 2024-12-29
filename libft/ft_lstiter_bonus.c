/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:08:52 by suroh             #+#    #+#             */
/*   Updated: 2024/04/30 14:30:06 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// void	f(void *content)
// {
// 	int	i;
// 	char	*c;
// 	c = content;
// 	i = 0;
// 	while (c[i] != '\0')
// 		c[i++] = '0';
// }

// int main()
// {
//     char content[] = "string";
//     t_list *new = ft_lstnew(content);
//     printf("%s\n", (char *)new->content);
//     ft_lstiter(new, f);
//     printf("%s\n", (char *)new->content);
//     free(new);
//     return 0;
// }