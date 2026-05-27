/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_row_parser_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:25:47 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 20:24:00 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_stream_reader.h"
#include "stream_row_parser.h"
#include <stdlib.h>
#include <unistd.h>

t_row	invalid_row(void)
{
	return ((t_row){.data = NULL, .size = 0, .y = 0});
}

int	free_row(t_row *row)
{
	if (!row || !row->data)
		return (0);
	free(row->data);
	*row = invalid_row();
	return (1);
}

int	stream_has_extra_data(t_file_stream *s)
{
	t_list_node		*node;
	t_stream_chunk	*chunk;
	char			tmp[1];
	int				r;

	if (!s)
		return (0);
	node = s->curr_node;
	if (node)
	{
		chunk = node->data;
		if (s->curr_offset < chunk->size)
			return (1);
		node = node->next;
	}
	while (node)
	{
		chunk = node->data;
		if (chunk && chunk->size > 0)
			return (1);
		node = node->next;
	}
	if (!s->eof)
	{
		r = read(s->fd, tmp, 1);
		if (r > 0)
		{
			s->eof = 0;
			return (1);
		}
		if (r == 0)
			s->eof = 1;
	}
	return (0);
}
