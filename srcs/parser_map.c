/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srungrit <srungrit@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 03:41:53 by srungrit          #+#    #+#             */
/*   Updated: 2026/05/26 15:56:59 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_map.h"

static int	get_line_len(char *str, int size, int i)
{
	int	len;

	len = 0;
	while (i + len < size && str[i + len] != '\n')
		len++;
	return (len);
}

static int	validate_charset(t_bsq_charset *charset)
{
	if (charset->empty == charset->obstacle || charset->empty == charset->full
		|| charset->obstacle == charset->full)
		return (0);
	return (charset->empty >= 32 && charset->empty <= 126
		&& charset->obstacle >= 32 && charset->obstacle <= 126
		&& charset->full >= 32 && charset->full <= 126);
}

static int	parser_header(char *ct, int size, int *height,
		t_bsq_charset *charset)
{
	int	len;
	int	i;

	len = get_line_len(ct, size, 0);
	if (len < 4)
		return (0);
	charset->empty = ct[len - 3];
	charset->obstacle = ct[len - 2];
	charset->full = ct[len - 1];
	if (!validate_charset(charset))
		return (0);
	*height = 0;
	i = -1;
	while (++i < len - 3)
	{
		if (ct[i] < '0' || ct[i] > '9')
			return (0);
		if (*height > (2147483647 - (ct[i] - '0')) / 10)
			return (0);
		*height = (*height * 10) + (ct[i] - '0');
	}
	return (*height > 0);
}

static int	parse_body_loop(t_bsq_map *m, char *ct, int size, int *i)
{
	int	row;
	int	col;

	row = 0;
	while (*i < size && row < m->y)
	{
		if (get_line_len(ct, size, *i) != m->x)
			return (0);
		col = 0;
		while (col < m->x)
		{
			if (ct[*i + col] == ct[get_line_len(ct, size, 0) - 3])
				bsq_map_write(*m, BSQ_MAP_EMPTY, col, row);
			else if (ct[*i + col] == ct[get_line_len(ct, size, 0) - 2])
				bsq_map_write(*m, BSQ_MAP_OBSTACLE, col, row);
			else
				return (0);
			col++;
		}
		*i += m->x + (*i + m->x < size && ct[*i + m->x] == '\n');
		row++;
	}
	return (row == m->y);
}

int	parser_map(char *content, int size, t_bsq_charset *charset, t_bsq_map *map)
{
	int	i;

	if (!map)
		return (0);
	*map = invalid_bsq_map();
	if (!content || size <= 0 || !parser_header(content, size, &map->y,
			charset))
		return (0);
	i = get_line_len(content, size, 0);
	if (i >= size || content[i++] != '\n')
		return (0);
	map->x = get_line_len(content, size, i);
	if (map->x <= 0 || !new_bsq_map(map->x, map->y, map))
		return (0);
	if (!parse_body_loop(map, content, size, &i) || i != size)
		return (free_bsq_map(map), 0);
	return (1);
}
