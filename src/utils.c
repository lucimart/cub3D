/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:32:38 by lucimart          #+#    #+#             */
/*   Updated: 2021/02/01 19:52:33 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libcub3d.h"

void	err(char *str, t_flags *flags)
{
	ft_putstr("Error\n");
	if (str)
	{
		ft_putstr(str);
		ft_putchar('\n');
	}
	flags->valid = 0;
}