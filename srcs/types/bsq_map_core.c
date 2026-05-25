/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:21:59 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 18:25:02 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/bsq_map.h"
#include <stdlib.h>

int	new_bsq_map(int x, int y, t_bsq_map *bsq_map)
{
	if (!bsq_map || x < 1 || y < 1)
		return (0);
	bsq_map->id_arr = malloc(x * y * sizeof(char));
	if (!bsq_map->id_arr)
		return (0);
	bsq_map->x = x;
	bsq_map->y = y;
	return (1);
}

int	free_bsq_map(t_bsq_map *bsq_map)
{
	if (!bsq_map || !bsq_map->id_arr)
		return (0);
	free(bsq_map->id_arr);
	bsq_map->id_arr = NULL;
	bsq_map->x = 0;
	bsq_map->y = 0;
	return (1);
}

t_bsq_map	invalid_bsq_map(void)
{
	return ((t_bsq_map){.id_arr = NULL, .x = 0, .y = 0});
}

char	bsq_map_lookup(t_bsq_map bsq_map, int col, int row)
{
	return (bsq_map.id_arr[col + row * bsq_map.x]);
}

void	bsq_map_write(t_bsq_map bsq_map, char id, int col, int row)
{
	bsq_map.id_arr[col + row * bsq_map.x] = id;
}
