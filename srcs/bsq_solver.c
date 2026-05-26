/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:47:23 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/26 17:55:15 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_solver.h"
#include <stdlib.h>

static void	mark_square(t_bsq_map map, int size, int end_x, int end_y)
{
	int	x;
	int	y;

	y = end_y - size + 1;
	while (y <= end_y)
	{
		x = end_x - size + 1;
		while (x <= end_x)
		{
			bsq_map_write(map, BSQ_MAP_FULL, x, y);
			x++;
		}
		y++;
	}
}

static int	get_square_size(t_bsq_map map, int *dp, int x, int y)
{
	int	min;
	int	top;
	int	left;
	int	diag;

	if (bsq_map_lookup(map, x, y) != BSQ_MAP_EMPTY)
		return (0);
	if (x == 0 || y == 0)
		return (1);
	top = dp[(y - 1) * map.x + x];
	left = dp[y * map.x + (x - 1)];
	diag = dp[(y - 1) * map.x + (x - 1)];
	min = top;
	if (min > left)
		min = left;
	if (min > diag)
		min = diag;
	return (min);
}

static void	fill_temp_map(t_bsq_map map, int *temp_map, t_bsq_solver_sqr *best)
{
	int	x;
	int	y;
	int	size;

	y = 0;
	while (y < map.y)
	{
		x = 0;
		while (x < map.x)
		{
			size = get_square_size(map, temp_map, x, y);
			temp_map[y * map.x + x] = size;
			if (size > best->size)
				*best = (t_bsq_solver_sqr){size, x, y};
			x++;
		}
		y++;
	}
}

int	mark_largest_square(t_bsq_map map, t_bsq_map result)
{
	int					*temp_map;
	t_bsq_solver_sqr	best;

	if (!map.id_arr || !result.id_arr)
		return (0);
	temp_map = malloc(sizeof(int) * map.x * map.y);
	if (!temp_map)
		return (-1);
	best = (t_bsq_solver_sqr){0, 0, 0};
	fill_temp_map(map, temp_map, &best);
	free(temp_map);
	if (best.size == 0)
		return (0);
	mark_square(result, best.size, best.x, best.y);
	return (1);
}
