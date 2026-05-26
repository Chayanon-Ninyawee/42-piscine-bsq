/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:26:08 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/26 14:53:38 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_solver.h"
#include "file_reader.h"
#include "parser_map.h"
#include "types/bsq_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	test_bsq_solver(void)
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
	return (1);
}

int	main(int argc, char **argv)
{
	t_file_data		file;
	t_bsq_charset	charset;
	t_bsq_map		map;
	t_bsq_map		result;

	if (argc != 2)
	{
		printf("Usage: %s <map_path>\n", argv[0]);
		return (0);
	}
	file = read_file_all(argv[1]);
	if (!file.data)
	{
		printf("Result: FAILED (Could not read file)\n");
		return (0);
	}
	map = parser_map(file.data, file.size, &charset);
	free(file.data);
	if (map.x <= 0 || map.y <= 0 || !map.id_arr)
	{
		printf("Result: INVALID MAP caught safely (map error).\n");
		return (0);
	}
	if (!new_bsq_map(map.x, map.y, &result))
	{
		printf("Can't malloc result map\n");
		return (0);
	}
	bsq_map_cpy(map, result);
	if (!mark_largest_square(map, result))
	{
		printf("Error\n");
		return (0);
	}
	print_bsq_map(map, charset);
	printf("\n====\n\n");
	print_bsq_map(result, charset);
	free_bsq_map(&map);
	free_bsq_map(&result);
	return (0);
}
