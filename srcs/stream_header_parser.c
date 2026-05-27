/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_header_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:19:20 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 17:47:56 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream_header_parser.h"
#include <stdlib.h>

static int	validate_charset(t_bsq_charset charset)
{
	if (charset.empty == charset.obstacle || charset.empty == charset.full
		|| charset.obstacle == charset.full)
		return (0);
	return (charset.empty >= 32 && charset.empty <= 126
		&& charset.obstacle >= 32 && charset.obstacle <= 126
		&& charset.full >= 32 && charset.full <= 126);
}

static int	parse_height(char *data, int size, int *height)
{
	int	i;

	*height = 0;
	i = 0;
	while (i < size)
	{
		if (data[i] < '0' || data[i] > '9')
			return (0);
		if (*height > (2147483647 - (data[i] - '0')) / 10)
			return (0);
		*height = (*height * 10) + (data[i] - '0');
		i++;
	}
	return (*height > 0);
}

static int	parse_charset(char *data, int size, t_bsq_charset *charset)
{
	if (size < 4)
		return (0);
	charset->empty = data[size - 4];
	charset->obstacle = data[size - 3];
	charset->full = data[size - 2];
	return (validate_charset(*charset));
}
int	parse_stream_header(t_file_stream *stream, t_stream_map_header *header)
{
	t_stream_data	line;

	if (!stream || !header)
		return (0);
	if (!stream_read_until(stream, '\n', &line))
		return (0);
	if (!parse_charset(line.data, line.size, &header->charset))
		return (free(line.data), 0);
	if (!parse_height(
			line.data,
			line.size - 4,
			&header->height))
		return (free(line.data), 0);
	free(line.data);
	return (1);
}
