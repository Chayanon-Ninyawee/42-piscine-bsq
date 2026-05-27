/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_row_parser.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 20:28:53 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 20:31:24 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STREAM_ROW_PARSER_H
# define STREAM_ROW_PARSER_H
# include "file_stream.h"
# include "stream_header_parser.h"
# define BSQ_MAP_EMPTY 0
# define BSQ_MAP_OBSTACLE 1
# define BSQ_MAP_FULL 2

typedef struct s_row
{
	char				*data;
	int					size;
	int					y;
}						t_row;

typedef struct s_row_parser
{
	t_file_stream		*stream;
	t_stream_map_header	header;
	int					width;
	int					y;
}						t_row_parser;

t_row					invalid_row(void);
int						free_row(t_row *row);

int						init_row_parser(t_row_parser *parser,
							t_file_stream *stream, t_stream_map_header header);
int						parse_next_row(t_row_parser *parser, t_row *row);

#endif
