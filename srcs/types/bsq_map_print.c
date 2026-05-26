/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:21:59 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/26 14:28:38 by cninyawe         ###   ########.fr       */
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

void	print_bsq_map(t_bsq_map bsq_map, t_bsq_charset charset)
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
				write(1, &charset.empty, 1);
			else if (id == BSQ_MAP_OBSTACLE)
				write(1, &charset.obstacle, 1);
			else if (id == BSQ_MAP_FULL)
				write(1, &charset.full, 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}
