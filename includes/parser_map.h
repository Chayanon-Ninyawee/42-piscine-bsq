/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srungrit <srungrit@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 22:51:31 by srungrit          #+#    #+#             */
/*   Updated: 2026/05/26 15:56:51 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_MAP_H
# define PARSER_MAP_H
# include "types/bsq_map.h"

// Create new t_bsq_map, if can't malloc return 0
int	parser_map(char *content, int size, t_bsq_charset *charset, t_bsq_map *map);

#endif
