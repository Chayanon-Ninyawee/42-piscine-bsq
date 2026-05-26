/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cninyawe <cninyawe@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:51:14 by cninyawe          #+#    #+#             */
/*   Updated: 2026/05/26 15:52:58 by cninyawe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_utils.h"
#include "str_utils.h"
#include <unistd.h>

void	print(char *str)
{
	write(1, str, ft_strlen(str));
}
