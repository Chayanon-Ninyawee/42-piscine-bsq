/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stream.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:42:35 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 17:12:39 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_STREAM_H
# define FILE_STREAM_H
# include "types/linked_list.h"
# define STREAM_BUFFER_SIZE 1024

typedef struct s_file_stream
{
	int				fd;

	t_linked_list	chunks;

	t_list_node		*curr_node;
	int				curr_offset;

	int				eof;
}					t_file_stream;

typedef struct s_stream_data
{
	char			*data;
	int				size;
}					t_stream_data;

int					open_file_stream(int fd, t_file_stream *stream);
void				close_file_stream(t_file_stream *stream);

t_stream_data		invalid_stream_data(void);
void				free_stream_data(t_stream_data *data);

int					stream_read_until(t_file_stream *stream, char c,
						t_stream_data *out);

#endif
