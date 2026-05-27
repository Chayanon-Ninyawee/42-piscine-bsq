/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_header_parser.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:18:57 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 17:47:41 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STREAM_HEADER_PARSER_H
# define STREAM_HEADER_PARSER_H
# include "file_stream.h"

typedef struct s_bsq_charset
{
	char			empty;
	char			obstacle;
	char			full;
}					t_bsq_charset;

typedef struct s_stream_map_header
{
	int				height;
	t_bsq_charset	charset;
}					t_stream_map_header;

int					parse_stream_header(t_file_stream *stream,
						t_stream_map_header *header);

#endif
