/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:11:05 by suroh             #+#    #+#             */
/*   Updated: 2024/11/12 21:39:42 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

// be aware while using this function because if this function is
// used before linking nodes, it will work like a lstclear.
// void	del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*new = ft_lstnew(ft_strdup("string"));
// 	t_list	*new1 = ft_lstnew(ft_strdup("tester"));
// 	ft_lstadd_back(&new, new1);
// 	printf("t_list *new's content is %s\n", (char *)new->content);
// 	printf("t_list *new1's content is %s\n", (char *)new->next->content);
// 	ft_lstdelone(new, del);
// 	printf("now the contents are deleted in new\n");
// 	free(new1->content);
// 	free(new1); //this is to delete the memory of the ft_strdup.
// 	printf("and the content of new1 is freed manually.\n");
// 	printf("It is because lstdelone only deletes chosen node.\n");
// 	return (0);
// }
