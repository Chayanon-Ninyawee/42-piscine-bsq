/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stream_reader_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:42:47 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 19:52:59 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_stream_reader.h"
#include <stdlib.h>
#include <unistd.h>

void	free_stream_chunk(void *ptr)
{
	t_stream_chunk	*chunk;

	chunk = ptr;
	if (!chunk)
		return ;
	free(chunk->data);
	free(chunk);
}

int	ensure_capacity(t_stream_read_ctx *ctx)
{
	char	*new_buf;
	int		new_cap;
	int		i;

	if (ctx->size < ctx->cap)
		return (1);
	new_cap = ctx->cap * 2;
	if (new_cap < 1024)
		new_cap = 1024;
	new_buf = malloc(new_cap);
	if (!new_buf)
		return (0);
	i = 0;
	while (i < ctx->size)
	{
		new_buf[i] = ctx->buf[i];
		i++;
	}
	free(ctx->buf);
	ctx->buf = new_buf;
	ctx->cap = new_cap;
	return (1);
}
