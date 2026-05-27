/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:14:43 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 19:48:10 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_solver.h"
#include "file_stream.h"
#include "stream_header_parser.h"
#include "stream_row_parser.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_full(t_bsq_square sqr, int x, int y)
{
	return (x >= sqr.x - sqr.size + 1 && x <= sqr.x && y >= sqr.y - sqr.size + 1
		&& y <= sqr.y);
}

static char	get_char(t_bsq_solver s, t_row row, int x, int y)
{
	if (is_full(s.best, x, y))
		return (s.parser.header.charset.full);
	if (row.data[x] == BSQ_MAP_EMPTY)
		return (s.parser.header.charset.empty);
	return (s.parser.header.charset.obstacle);
}

static int	open_parser(
	char *path,
	t_file_stream *stream,
	t_row_parser *parser)
{
	t_stream_map_header	header;
	int					fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!open_file_stream(fd, stream))
		return (close(fd), 0);
	if (!parse_stream_header(stream, &header))
		return (close_file_stream(stream), close(fd), 0);
	if (!init_row_parser(parser, stream, header))
		return (close_file_stream(stream), close(fd), 0);
	return (fd);
}

static void	print_row(t_bsq_solver s, t_row row)
{
	int		x;
	int		i;
	char	c;
	char	*buf;

	buf = malloc(s.parser.width + 1);
	if (!buf)
		return ;
	x = 0;
	i = 0;
	while (x < row.size)
	{
		c = get_char(s, row, x, row.y);
		buf[i++] = c;
		x++;
	}
	buf[i++] = '\n';
	write(1, buf, i);
	free(buf);
}

void	print_bsq_solution(char *path, t_bsq_solver solver)
{
	t_file_stream	stream;
	t_row_parser	parser;
	t_row			row;
	int				fd;

	fd = open_parser(path, &stream, &parser);
	if (!fd)
		return ;
	while (parse_next_row(&parser, &row))
	{
		print_row(solver, row);
		free_row(&row);
	}
	close_file_stream(&stream);
	close(fd);
}
