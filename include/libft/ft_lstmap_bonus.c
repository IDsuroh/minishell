/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:18:09 by suroh             #+#    #+#             */
/*   Updated: 2024/05/05 17:11:54 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	node = NULL;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&node, del);
			return (NULL);
		}
		ft_lstadd_back(&node, temp);
		lst = lst->next;
	}
	return (node);
}

// void	del(void *content)
// {
// 	free(content);
// }

// void	*funct(void *content)
// {
// 	int	i;
// 	char	*c = (char *)content;
// 	i = 0;
// 	while (c[i])
// 		c[i++] = '0';
// 	c[i] = '\0';
// 	return (c);
// }

// int	main(void)
// {
// 	t_list	*list1;
// 	t_list	*list2;
// 	t_list	*list3;
// 	t_list	*newlist;
// 	t_list	*freelist1;
// 	list1 = ft_lstnew(ft_strdup("Hello"));
// 	list2 = ft_lstnew(ft_strdup("This"));
// 	list3 = ft_lstnew(ft_strdup("IsZero"));
// 	list1->next = list2;
// 	list2->next = list3;
// 	freelist1 = list1;
// 	newlist = ft_lstmap(list1, &funct, &del);
// 	while (newlist)
//    	{
//       	printf("%s\n", (char *)newlist->content);
// 		t_list *temp = newlist;
// 	        newlist = newlist->next;
//         	free(temp->content);
//         	free(temp);
// 	}
// 	while (freelist1)
// 	{
// 		t_list *frfr1 = freelist1->next;
// 		free(freelist1);
// 		freelist1 = frfr1;
// 	}
// 	return (0);
// }
