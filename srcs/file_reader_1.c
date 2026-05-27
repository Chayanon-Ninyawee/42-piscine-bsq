/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:02:41 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 13:19:18 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_reader.h"
#include <stdlib.h>

t_file_data	invalid_file_data(void)
{
	return ((t_file_data){.data = NULL, .size = 0});
}

void	free_chunk(void *ptr)
{
	t_chunk	*chunk;

	chunk = ptr;
	if (!chunk)
		return ;
	free(chunk->data);
	free(chunk);
}
