/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stream_reader.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:11:57 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 19:52:22 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_STREAM_READER_H
# define FILE_STREAM_READER_H

# include "file_stream.h"

typedef struct s_stream_chunk
{
	char	*data;
	int		size;
}			t_stream_chunk;

typedef struct s_stream_read_ctx
{
	char	*buf;
	int		size;
	int		cap;
	char	c;
}			t_stream_read_ctx;

int			append_stream_chunk(t_file_stream *stream, char *buf, int size);
int			fill_stream(t_file_stream *stream);
int			finish_stream_read(t_stream_data *out, t_stream_read_ctx ctx);
int			read_chunk_until(t_file_stream *stream, t_stream_chunk *chunk,
				t_stream_read_ctx *ctx, t_stream_data *out);
int			next_stream_chunk(t_file_stream *stream, char *buf);

void		free_stream_chunk(void *ptr);
int			ensure_capacity(t_stream_read_ctx *ctx);

#endif
