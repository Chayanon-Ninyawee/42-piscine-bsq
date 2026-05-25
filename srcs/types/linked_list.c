/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:57:34 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 19:57:54 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/linked_list.h"
#include <stdlib.h>

t_linked_list	new_linked_list(void)
{
	return ((t_linked_list){
		.head = NULL,
		.tail = NULL,
		.size = 0});
}

void	free_linked_list(t_linked_list *list, void (*free_func)(void *))
{
	t_list_node	*node;
	t_list_node	*next;

	if (!list)
		return ;
	node = list->head;
	while (node)
	{
		next = node->next;
		if (free_func)
			free_func(node->data);
		free(node);
		node = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

int	append_linked_list(t_linked_list *list, void *data)
{
	t_list_node	*node;

	if (!list)
		return (0);
	node = malloc(sizeof(t_list_node));
	if (!node)
		return (0);
	node->data = data;
	node->next = NULL;
	if (!list->head)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->size++;
	return (1);
}

void	**linked_list_to_array(t_linked_list list)
{
	void		**arr;
	t_list_node	*node;
	int			i;

	arr = malloc(sizeof(void *) * (list.size + 1));
	if (!arr)
		return (NULL);
	node = list.head;
	i = 0;
	while (node)
	{
		arr[i++] = node->data;
		node = node->next;
	}
	arr[i] = NULL;
	return (arr);
}
