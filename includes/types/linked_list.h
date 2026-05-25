/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:53:49 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 20:05:49 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

typedef struct s_list_node
{
	void				*data;
	struct s_list_node	*next;
}						t_list_node;

typedef struct s_linked_list
{
	t_list_node			*head;
	t_list_node			*tail;
	int					size;
}						t_linked_list;

t_linked_list			new_linked_list(void);
void					free_linked_list(t_linked_list *list,
							void (*free_func)(void *));

int						append_linked_list(t_linked_list *list, void *data);

void					**linked_list_to_array(t_linked_list list);
#endif
