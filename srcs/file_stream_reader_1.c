/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stream_reader_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:42:47 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 20:08:39 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_stream_reader.h"
#include <stdlib.h>
#include <unistd.h>

int	append_stream_chunk(t_file_stream *stream, char *buf, int size)
{
	t_stream_chunk	*chunk;
	int				i;

	chunk = malloc(sizeof(t_stream_chunk));
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
	if (!append_linked_list(&stream->chunks, chunk))
		return (free(chunk->data), free(chunk), 0);
	return (1);
}

int	fill_stream(t_file_stream *stream)
{
	char	buf[STREAM_BUFFER_SIZE];
	int		read_size;

	if (stream->eof)
		return (1);
	read_size = read(stream->fd, buf, sizeof(buf));
	if (read_size < 0)
		return (0);
	if (read_size == 0)
	{
		stream->eof = 1;
		return (1);
	}
	return (append_stream_chunk(stream, buf, read_size));
}

int	finish_stream_read(t_stream_data *out, t_stream_read_ctx ctx)
{
	out->data = ctx.buf;
	out->size = ctx.size;
	return (1);
}

int	read_chunk_until(t_file_stream *stream, t_stream_chunk *chunk,
		t_stream_read_ctx *ctx, t_stream_data *out)
{
	while (stream->curr_offset < chunk->size)
	{
		if (!ensure_capacity(ctx))
			return (0);
		ctx->buf[ctx->size] = chunk->data[stream->curr_offset];
		ctx->size++;
		if (chunk->data[stream->curr_offset] == ctx->c)
		{
			stream->curr_offset++;
			return (finish_stream_read(out, *ctx));
		}
		stream->curr_offset++;
	}
	if (!stream->curr_node->next && stream->eof)
	{
		if (!ensure_capacity(ctx))
			return (0);
		ctx->buf[ctx->size++] = '\n';
		return (finish_stream_read(out, *ctx));
	}
	return (0);
}

int	next_stream_chunk(t_file_stream *stream, char *buf)
{
	stream->curr_node = stream->curr_node->next;
	stream->curr_offset = 0;
	if (!stream->curr_node)
	{
		if (!fill_stream(stream))
			return (free(buf), 0);
		stream->curr_node = stream->chunks.tail;
	}
	return (1);
}
