/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:02:41 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 20:05:29 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_reader.h"
#include "types/linked_list.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static t_file_data	invalid_file_data(void)
{
	return ((t_file_data){.data = NULL, .size = 0});
}

static char	*list_to_char_array(t_linked_list list)
{
	char		*arr;
	t_list_node	*node;
	int			i;

	arr = malloc(sizeof(char) * list.size);
	if (!arr)
		return (NULL);
	node = list.head;
	i = 0;
	while (node)
	{
		arr[i++] = *(char *)node->data;
		node = node->next;
	}
	return (arr);
}

static int	open_file(char *path, int *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		return (0);
	return (1);
}

static int	append_buffer(t_linked_list *list, char *buf, int size)
{
	char	*c;
	int		i;

	i = 0;
	while (i < size)
	{
		c = malloc(sizeof(char));
		if (!c)
			return (0);
		*c = buf[i];
		if (!append_linked_list(list, c))
			return (free(c), 0);
		i++;
	}
	return (1);
}

t_file_data	read_file_all(char *path)
{
	t_linked_list	list;
	t_file_data		file_data;
	int				fd;
	int				read_size;
	char			buf[BUFFER_SIZE];

	if (!open_file(path, &fd))
		return (invalid_file_data());
	list = new_linked_list();
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		if (!append_buffer(&list, buf, read_size))
			return (close(fd), free_linked_list(&list, free),
				invalid_file_data());
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	close(fd);
	file_data.data = list_to_char_array(list);
	file_data.size = list.size;
	free_linked_list(&list, free);
	if (!file_data.data)
		return (invalid_file_data());
	return (file_data);
}
