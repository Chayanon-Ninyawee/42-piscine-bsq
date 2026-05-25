/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:26:08 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 19:51:21 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_solver.h"
#include "types/bsq_map.h"
#include <stdio.h>

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
