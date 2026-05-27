/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:46:43 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/27 18:10:11 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_SOLVER_H
# define BSQ_SOLVER_H
# include "stream_row_parser.h"

typedef struct s_bsq_square
{
	int				x;
	int				y;
	int				size;
}					t_bsq_square;

typedef struct s_bsq_solver
{
	t_row_parser	parser;
	int				*prev;
	int				*curr;
	t_bsq_square	best;
}					t_bsq_solver;

int					init_bsq_solver(t_bsq_solver *solver, t_row_parser parser);
void				free_bsq_solver(t_bsq_solver *solver);
int					solve_bsq(t_bsq_solver *solver);

void				print_bsq_solution(char *path, t_bsq_solver solver);

#endif
