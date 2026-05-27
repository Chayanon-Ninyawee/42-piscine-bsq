/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_row_parser_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:25:47 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 20:24:55 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_stream.h"
#include "stream_row_parser.h"
#include <stdlib.h>

int	init_row_parser(t_row_parser *parser, t_file_stream *stream,
		t_stream_map_header header)
{
	if (!parser || !stream)
		return (0);
	parser->stream = stream;
	parser->header = header;
	parser->width = -1;
	parser->y = 0;
	return (1);
}

static int	parse_cell(t_stream_map_header header, char *dst, char c, int i)
{
	if (c == header.charset.empty)
		dst[i] = BSQ_MAP_EMPTY;
	else if (c == header.charset.obstacle)
		dst[i] = BSQ_MAP_OBSTACLE;
	else
		return (0);
	return (1);
}

static int	parse_row(t_row_parser *parser, t_stream_data line, t_row *row)
{
	int	i;
	int	width;

	width = line.size - 1;
	if (parser->width == -1)
		parser->width = width;
	if (width != parser->width || width <= 0)
		return (0);
	row->data = malloc(width);
	if (!row->data)
		return (0);
	i = 0;
	while (i < width)
	{
		if (!parse_cell(parser->header, row->data, line.data[i], i))
			return (free_row(row), 0);
		i++;
	}
	row->size = width;
	row->y = parser->y;
	return (1);
}

int	parse_next_row(t_row_parser *parser, t_row *row)
{
	t_stream_data	line;

	if (!parser || !row)
		return (0);
	*row = invalid_row();
	if (parser->y >= parser->header.height)
		return (0);
	if (!stream_read_until(parser->stream, '\n', &line))
		return (0);
	if (!parse_row(parser, line, row))
		return (free_stream_data(&line), 0);
	free_stream_data(&line);
	parser->y++;
	return (1);
}
