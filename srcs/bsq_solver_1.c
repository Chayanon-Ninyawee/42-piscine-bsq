/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:47:23 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 18:52:23 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_solver.h"
#include <stdlib.h>

int	init_bsq_solver(t_bsq_solver *solver, t_row_parser parser)
{
	if (!solver)
		return (0);
	solver->parser = parser;
	solver->prev = NULL;
	solver->curr = NULL;
	solver->best = (t_bsq_square){0, 0, 0};
	return (1);
}

void	free_bsq_solver(t_bsq_solver *solver)
{
	if (!solver)
		return ;
	free(solver->prev);
	free(solver->curr);
}
