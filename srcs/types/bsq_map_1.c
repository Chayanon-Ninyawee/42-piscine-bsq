/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:21:59 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 19:42:12 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/bsq_map.h"
#include <stdlib.h>

int	bsq_map_cpy(t_bsq_map src, t_bsq_map dst)
{
	int	col;
	int	row;
	int	id;

	if (!src.id_arr || !dst.id_arr || src.x != dst.x || src.y != dst.y)
		return (0);
	row = 0;
	while (row < src.y)
	{
		col = 0;
		while (col < src.x)
		{
			id = bsq_map_lookup(src, col, row);
			bsq_map_write(dst, id, col, row);
			col++;
		}
		row++;
	}
	return (1);
}
