/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:42:47 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 19:53:53 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_stream.h"
#include "file_stream_reader.h"
#include <stdlib.h>

int	open_file_stream(int fd, t_file_stream *stream)
{
	if (!stream || fd < 0)
		return (0);
	stream->fd = fd;
	stream->chunks = new_linked_list();
	stream->curr_node = NULL;
	stream->curr_offset = 0;
	stream->eof = 0;
	return (1);
}

void	close_file_stream(t_file_stream *stream)
{
	if (!stream)
		return ;
	stream->fd = -1;
	free_linked_list(&stream->chunks, free_stream_chunk);
	stream->curr_node = NULL;
	stream->curr_offset = 0;
	stream->eof = 1;
}

t_stream_data	invalid_stream_data(void)
{
	return ((t_stream_data){.data = NULL, .size = 0});
}

void	free_stream_data(t_stream_data *data)
{
	if (!data)
		return ;
	free(data->data);
	*data = invalid_stream_data();
}

int	stream_read_until(t_file_stream *stream, char c, t_stream_data *out)
{
	t_stream_chunk		*chunk;
	t_stream_read_ctx	ctx;

	if (!stream || !out)
		return (0);
	*out = invalid_stream_data();
	if (!fill_stream(stream))
		return (0);
	if (!stream->curr_node)
		stream->curr_node = stream->chunks.head;
	ctx.cap = 1024;
	ctx.buf = malloc(ctx.cap);
	if (!ctx.buf)
		return (0);
	ctx.size = 0;
	ctx.c = c;
	while (stream->curr_node)
	{
		chunk = stream->curr_node->data;
		if (read_chunk_until(stream, chunk, &ctx, out))
			return (1);
		if (!next_stream_chunk(stream, ctx.buf))
			return (0);
	}
	return (finish_stream_read(out, ctx) && ctx.size > 0);
}
