/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:02:41 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 20:30:28 by cninyawe         ###   ########.fr       */
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

static int	append_buffer(t_linked_list *list, char *buf, int size)
{
	char	*chunk;
	int		i;

	chunk = malloc(sizeof(char) * size);
	if (!chunk)
		return (0);
	i = 0;
	while (i < size)
	{
		chunk[i] = buf[i];
		i++;
	}
	if (!append_linked_list(list, chunk))
		return (free(chunk), 0);
	return (1);
}

static char	*list_to_char_array(t_linked_list list, int total_size)
{
	char		*arr;
	t_list_node	*node;
	char		*chunk;
	int			i;
	int			j;

	arr = malloc(sizeof(char) * total_size);
	if (!arr)
		return (NULL);
	node = list.head;
	i = 0;
	while (node)
	{
		chunk = node->data;
		j = 0;
		while (j < BUFFER_SIZE && i < total_size)
			arr[i++] = chunk[j++];
		node = node->next;
	}
	return (arr);
}

static int	read_to_list(int fd, t_linked_list *list, int *total_size)
{
	int		read_size;
	char	buf[BUFFER_SIZE];

	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		if (!append_buffer(list, buf, read_size))
			return (0);
		*total_size += read_size;
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	return (1);
}

t_file_data	read_file_all(char *path)
{
	t_linked_list	list;
	t_file_data		file_data;
	int				fd;
	int				total_size;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (invalid_file_data());
	list = new_linked_list();
	total_size = 0;
	if (!read_to_list(fd, &list, &total_size))
		return (close(fd), free_linked_list(&list, free), invalid_file_data());
	close(fd);
	file_data.data = list_to_char_array(list, total_size);
	file_data.size = total_size;
	free_linked_list(&list, free);
	if (!file_data.data)
		return (invalid_file_data());
	return (file_data);
}
