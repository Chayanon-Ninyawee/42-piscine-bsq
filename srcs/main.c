/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:26:08 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 19:42:49 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/bsq_map.h"
#include <stdio.h>

int	is_square_placement_valid(t_bsq_map map, int size, int sqr_col, int sqr_row)
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

int	mark_largest_square(t_bsq_map map, t_bsq_map result)
{
	int	size;
	int	col;
	int	row;

	if (!map.id_arr || !result.id_arr || map.x != result.x || map.y != result.y)
		return (0);
	size = map.x;
	if (map.y < map.x)
		size = map.y;
	while (size >= 1)
	{
		row = 0;
		while (row < map.y - (size - 1))
		{
			col = 0;
			while (col < map.x - (size - 1))
			{
				if (is_square_placement_valid(map, size, col, row))
					return (mark_square(result, size, col, row), 1);
				col++;
			}
			row++;
		}
		size--;
	}
	return (0);
}

int	main(void)
{
	t_bsq_map	map;
	t_bsq_map	result;
	int			x;
	int			y;

	if (!new_bsq_map(7, 5, &map))
		return (0);
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 7)
		{
			bsq_map_write(map, 0, x, y);
			x++;
		}
		y++;
	}
	bsq_map_write(map, 1, 2, 2);
	if (!new_bsq_map(7, 5, &result))
		return (0);
	bsq_map_cpy(map, result);
	if (!mark_largest_square(map, result))
	{
		printf("Error\n");
		return (0);
	}
	printf("====\n\n");
	print_bsq_map(map, (t_bsq_charset){'-', '0', '#'});
	printf("\n====\n\n");
	print_bsq_map(result, (t_bsq_charset){'-', '0', '#'});
	printf("\n====\n");
	free_bsq_map(&map);
	free_bsq_map(&result);
	return (0);
}
