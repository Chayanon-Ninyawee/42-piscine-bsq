/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:21:35 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/25 19:40:53 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_MAP_H
# define BSQ_MAP_H

typedef struct s_bsq_charset
{
	char	empty;
	char	obstacle;
	char	full;
}			t_bsq_charset;

typedef struct s_bsq_map
{
	char	*id_arr;
	int		x;
	int		y;
}			t_bsq_map;

int			new_bsq_map(int x, int y, t_bsq_map *bsq_map);
int			free_bsq_map(t_bsq_map *bsq_map);

t_bsq_map	invalid_bsq_map(void);

char		bsq_map_lookup(t_bsq_map bsq_map, int col, int row);
void		bsq_map_write(t_bsq_map bsq_map, char id, int col, int row);

int			bsq_map_cpy(t_bsq_map src, t_bsq_map dst);

void		print_bsq_map_raw(t_bsq_map bsq_map);
void		print_bsq_map(t_bsq_map bsq_map, t_bsq_charset charset);

#endif
