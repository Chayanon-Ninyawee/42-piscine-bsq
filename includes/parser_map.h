/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srungrit <srungrit@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 22:51:31 by srungrit          #+#    #+#             */
/*   Updated: 2026/05/25 23:23:52 by srungrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_MAP_H
# define PARSER_MAP_H

# include "types/bsq_map.h"

# define BSQ_EMPTY 0
# define BSQ_OBSTACLE 1

t_bsq_map	parser_map(char *content, int size, t_bsq_charset *charset);

#endif
