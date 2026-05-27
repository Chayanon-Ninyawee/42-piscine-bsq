/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:47:23 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 19:20:30 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_solver.h"
#include <stdlib.h>

static int	init_solver_buf(t_bsq_solver *solver, int width)
{
	solver->prev = malloc(sizeof(int) * width);
	if (!solver->prev)
		return (0);
	solver->curr = malloc(sizeof(int) * width);
	if (!solver->curr)
		return (free(solver->prev), 0);
	return (1);
}

static int	get_square_size(t_bsq_solver *solver, t_row row, int x)
{
	int	min;
	int	top;
	int	diag;
	int	left;

	if (row.data[x] != BSQ_MAP_EMPTY)
		return (0);
	if (x == 0 || row.y == 0)
		return (1);
	top = solver->prev[x];
	diag = solver->prev[x - 1];
	left = solver->curr[x - 1];
	min = top;
	if (min > diag)
		min = diag;
	if (min > left)
		min = left;
	return (min + 1);
}

static void	update_best(t_bsq_solver *solver, int size, int x, int y)
{
	if (size > solver->best.size)
	{
		solver->best.size = size;
		solver->best.x = x;
		solver->best.y = y;
	}
}

static void	swap_rows(t_bsq_solver *solver)
{
	int	*tmp;

	tmp = solver->prev;
	solver->prev = solver->curr;
	solver->curr = tmp;
}

int	solve_bsq(t_bsq_solver *solver)
{
	t_row	row;
	int		x;

	while (parse_next_row(&solver->parser, &row))
	{
		if (!solver->curr)
		{
			if (!init_solver_buf(solver, row.size))
				return (free_row(&row), 0);
			solver->parser.width = row.size;
		}
		x = 0;
		while (x < row.size)
		{
			solver->curr[x] = get_square_size(solver, row, x);
			update_best(solver, solver->curr[x], x, row.y);
			x++;
		}
		free_row(&row);
		swap_rows(solver);
	}
	return (solver->parser.y == solver->parser.header.height);
}
