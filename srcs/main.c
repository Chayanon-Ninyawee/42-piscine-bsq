/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:26:08 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/26 16:39:45 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_solver.h"
#include "file_reader.h"
#include "parser_map.h"
#include "print_utils.h"
#include "types/bsq_map.h"
#include <stdlib.h>

static int	solve_and_print(t_file_data file_data)
{
	t_bsq_charset	charset;
	t_bsq_map		map;
	t_bsq_map		result;

	if (!parser_map(file_data.data, file_data.size, &charset, &map))
		return (print("map error\n"), 0);
	if (!new_bsq_map(map.x, map.y, &result))
		return (-1);
	bsq_map_cpy(map, result);
	if (!mark_largest_square(map, result))
		return (print("map error\n"), 0);
	print_bsq_map(result, charset);
	free_bsq_map(&map);
	free_bsq_map(&result);
	return (1);
}

static int	solve_stdin(void)
{
	t_file_data	file_data;

	if (!read_fd_all(0, &file_data))
		return (print("map error\n"), 0);
	solve_and_print(file_data);
	free(file_data.data);
	return (1);
}
static int	solve_files(int argc, char **argv)
{
	t_file_data	file_data;
	int			i;

	i = 1;
	while (i < argc)
	{
		if (!read_file_all(argv[i], &file_data))
			return (print("map error\n"), 0);
		solve_and_print(file_data);
		if (i < argc - 1)
			print("\n");
		free(file_data.data);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 1)
		return (0);
	else if (argc == 1)
		solve_stdin();
	else
		solve_files(argc, argv);
	return (0);
}
