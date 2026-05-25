/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:46:43 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 19:48:08 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_SOLVER_H
# define BSQ_SOLVER_H

# include "types/bsq_map.h"

void	mark_square(t_bsq_map map, int size, int sqr_col, int sqr_row);
int		mark_largest_square(t_bsq_map map, t_bsq_map result);

#endif
