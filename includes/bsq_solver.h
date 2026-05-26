/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:46:43 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/26 17:54:42 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_SOLVER_H
# define BSQ_SOLVER_H

# include "types/bsq_map.h"

typedef struct s_bsq_solver_sqr
{
	int	size;
	int	x;
	int	y;
}		t_bsq_solver_sqr;

int		mark_largest_square(t_bsq_map map, t_bsq_map result);

#endif
