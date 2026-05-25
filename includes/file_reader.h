/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:02:15 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 20:05:22 by cninyawe         ###   ########.fr       */
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

t_file_data	read_file_all(char *path);

#endif
