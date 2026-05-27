/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:21:59 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 19:53:29 by srungrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/bsq_map.h"
#include <stdlib.h>
#include <unistd.h>

void	print_bsq_map_raw(t_bsq_map bsq_map)
{
	int	col;
	int	row;
	int	id;

	row = 0;
	while (row < bsq_map.y)
	{
		col = 0;
		while (col < bsq_map.x)
		{
			id = bsq_map_lookup(bsq_map, col, row);
			if (id == BSQ_MAP_EMPTY)
				write(1, "0", 1);
			else if (id == BSQ_MAP_OBSTACLE)
				write(1, "1", 1);
			else if (id == BSQ_MAP_FULL)
				write(1, "2", 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

static char	get_map_char(int id, t_bsq_charset cs)
{
	if (id == BSQ_MAP_EMPTY)
		return (cs.empty);
	if (id == BSQ_MAP_OBSTACLE)
		return (cs.obstacle);
	return (cs.full);
}

void	print_bsq_map(t_bsq_map map, t_bsq_charset cs)
{
	char	*line;
	int		x;
	int		y;

	line = malloc(map.x + 1);
	if (!line)
		return ;
	y = 0;
	while (y < map.y)
	{
		x = 0;
		while (x < map.x)
		{
			line[x] = get_map_char(bsq_map_lookup(map, x, y), cs);
			x++;
		}
		line[map.x] = '\n';
		write(1, line, map.x + 1);
		y++;
	}
	free(line);
}
