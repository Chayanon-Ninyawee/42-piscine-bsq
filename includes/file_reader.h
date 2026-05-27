/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:02:15 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 13:19:17 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_READER_H
# define FILE_READER_H
# define BUFFER_SIZE 1024

typedef struct s_file_data
{
	char	*data;
	int		size;
}			t_file_data;

typedef struct s_chunk
{
	char	*data;
	int		size;
}			t_chunk;

t_file_data	invalid_file_data(void);
void		free_chunk(void *ptr);
int			read_fd_all(int fd, t_file_data *file_data);
int			read_file_all(char *path, t_file_data *file_data);

#endif
