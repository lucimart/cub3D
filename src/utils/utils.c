/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 23:24:29 by lucimart          #+#    #+#             */
/*   Updated: 2020/10/03 23:25:00 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libcub3d.h"

int  amount_of(char **arr, char c)
{
    int i;
    int j;
    int amount;

    i = -1;
    j = -1;
    amount = 0;
    while (arr[++i])
    {
        while (arr[i][++j])
            if (arr[i][j] == c)
                amount++;
        j = -1;
    }
    return (amount);
}
