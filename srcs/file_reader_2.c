/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:02:41 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 13:21:55 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_reader.h"
#include "types/linked_list.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	append_buffer(t_linked_list *list, char *buf, int size)
{
	t_chunk	*chunk;
	int		i;

	chunk = malloc(sizeof(t_chunk));
	if (!chunk)
		return (0);
	chunk->data = malloc(size);
	if (!chunk->data)
		return (free(chunk), 0);
	chunk->size = size;
	i = 0;
	while (i < size)
	{
		chunk->data[i] = buf[i];
		i++;
	}
	if (!append_linked_list(list, chunk))
		return (free(chunk->data), free(chunk), 0);
	return (1);
}

static char	*list_to_char_array(t_linked_list list, int total_size)
{
	char		*arr;
	t_list_node	*node;
	t_chunk		*chunk;
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
		while (j < chunk->size && i < total_size)
			arr[i++] = chunk->data[j++];
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

int	read_fd_all(int fd, t_file_data *file_data)
{
	t_linked_list	list;
	int				total_size;

	if (!file_data)
		return (0);
	*file_data = invalid_file_data();
	if (fd < 0)
		return (0);
	list = new_linked_list();
	total_size = 0;
	if (!read_to_list(fd, &list, &total_size))
		return (free_linked_list(&list, free_chunk), 0);
	file_data->data = list_to_char_array(list, total_size);
	file_data->size = total_size;
	free_linked_list(&list, free_chunk);
	return (file_data->data != NULL);
}

int	read_file_all(char *path, t_file_data *file_data)
{
	int	fd;
	int	success;

	if (!file_data)
		return (0);
	*file_data = invalid_file_data();
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	success = read_fd_all(fd, file_data);
	close(fd);
	return (success);
}
