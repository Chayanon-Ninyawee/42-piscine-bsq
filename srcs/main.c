/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:26:08 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 19:21:44 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_solver.h"
#include "print_utils.h"
#include <fcntl.h>
#include <unistd.h>

static int	solve_file(char *path)
{
	t_file_stream		stream;
	t_stream_map_header	header;
	t_row_parser		parser;
	t_bsq_solver		solver;
	int					fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print("map error\n"), 0);
	if (!open_file_stream(fd, &stream))
		return (close(fd), 0);
	if (!parse_stream_header(&stream, &header))
		return (close_file_stream(&stream), close(fd), print("map error\n"), 0);
	if (!init_row_parser(&parser, &stream, header))
		return (close_file_stream(&stream), close(fd), 0);
	if (!init_bsq_solver(&solver, parser))
		return (close_file_stream(&stream), close(fd), 0);
	if (!solve_bsq(&solver))
		return (free_bsq_solver(&solver), close_file_stream(&stream), close(fd),
			print("map error\n"), 0);
	close_file_stream(&stream);
	close(fd);
	print_bsq_solution(path, solver);
	free_bsq_solver(&solver);
	return (1);
}

static int	solve_files(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		solve_file(argv[i]);
		if (i < argc - 1)
			print("\n");
		i++;
	}
	return (1);
}

// static int	solve_stdin(void)
// {
// 	if (!solve_and_print(0))
// 		return (print("map error\n"), 0);
// 	return (1);
// }

int	main(int argc, char **argv)
{
	if (argc < 1)
		return (0);
	else if (argc == 1)
		return (0);
	// solve_stdin();
	else
		solve_files(argc, argv);
	return (0);
}
