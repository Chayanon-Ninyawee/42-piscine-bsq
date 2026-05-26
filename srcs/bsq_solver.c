/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:47:23 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/26 15:14:01 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_solver.h"

static int	is_square_valid(t_bsq_map map, int size, int sqr_col, int sqr_row)
{
	int	col;
	int	row;

	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			if (bsq_map_lookup(map, col + sqr_col, row + sqr_row) != 0)
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

void	mark_square(t_bsq_map map, int size, int sqr_col, int sqr_row)
{
	int	col;
	int	row;

	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			bsq_map_write(map, 2, col + sqr_col, row + sqr_row);
			col++;
		}
		row++;
	}
}

static int	try_mark_square(t_bsq_map map, t_bsq_map result, int size)
{
	int	col;
	int	row;

	row = 0;
	while (row < map.y - (size - 1))
	{
		col = 0;
		while (col < map.x - (size - 1))
		{
			if (is_square_valid(map, size, col, row))
				return (mark_square(result, size, col, row), 1);
			col++;
		}
		row++;
	}
	return (0);
}

int	mark_largest_square(t_bsq_map map, t_bsq_map result)
{
	int	size;

	if (!map.id_arr || !result.id_arr)
		return (0);
	if (map.x != result.x || map.y != result.y)
		return (0);
	size = map.x;
	if (map.y < map.x)
		size = map.y;
	while (size >= 1)
	{
		if (try_mark_square(map, result, size))
			return (1);
		size--;
	}
	return (2);
}
