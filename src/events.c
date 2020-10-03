/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:07:12 by lucimart          #+#    #+#             */
/*   Updated: 2020/10/04 01:31:36 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libcub3d.h"

int             close_win(int keycode, t_conf *conf)
{
    if (keycode == KEY_ESC || keycode == BTN_X)
		mlx_destroy_window(conf->mlx, conf->win);
}