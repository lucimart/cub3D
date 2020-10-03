/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 23:21:01 by lucimart          #+#    #+#             */
/*   Updated: 2020/10/03 23:57:58 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libcub3d.h"

static void	check_resolution(t_conf *conf, char **arr)
{
    int i;
    int screen_x;
    int screen_y;

    i = -1;
    if (!(!conf->x && !conf->y && arr[1] && arr[2]) && (conf->err = 1))
        return ;
    while (!conf->err && arr[++i])
    {
        if (i == 1)
            conf->x = ft_atoi(arr[i]);
        else if (i == 2)
            conf->y = ft_atoi(arr[i]);
        else if (i > 2 && (conf->err = 1))
            break;
    }
    if (!conf->err && conf->x <= 0 || conf->y <= 0)
        conf->err = 1;
    if (!conf->err && (!ft_strequ(arr[1], ft_itoa(conf->x)) ||
        !ft_strequ(arr[2], ft_itoa(conf->y))))
        conf->err = 1;
    mlx_get_screen_size(conf->mlx, &screen_x, &screen_y);
    conf->x = (conf->x > screen_x) ? screen_x : conf->x;
    conf->y = (conf->y > screen_y) ? screen_y : conf->y;
}

static void	check_sprite(t_conf *conf, char **arr)
{
    int fd;

    if ((ft_strequ(arr[0], "NO") && conf->no) ||
        (ft_strequ(arr[0], "SO") && conf->so) ||
        (ft_strequ(arr[0], "EA") && conf->ea) ||
        (ft_strequ(arr[0], "WE") && conf->we) || (arr[1] && arr[2]) ||
        (ft_strequ(arr[0], "S") && conf->sprite) || !arr[1] ||
        ((fd = open(arr[1], O_RDONLY)) < 0) || close(fd) ||
        (!is_ext(arr[1], ".xpm") && !is_ext(arr[1], ".png")))
        conf->err = 1;
    if (!conf->err && ft_strequ(arr[0], "NO"))
        conf->no = ft_strdup(arr[1]);
    else if (!conf->err && ft_strequ(arr[0], "SO"))
        conf->so = ft_strdup(arr[1]);
    else if (!conf->err && ft_strequ(arr[0], "EA"))
        conf->ea = ft_strdup(arr[1]);
    else if (!conf->err && ft_strequ(arr[0], "WE"))
        conf->we = ft_strdup(arr[1]);
    else if (!conf->err && ft_strequ(arr[0], "S"))
        conf->sprite = ft_strdup(arr[1]);
}

static int	check_color(t_conf *conf, char **arr)
{
    int     color;
    int     i;
    char    *str;
    char    **clr;

    if ((i = -1) && ((ft_strequ(*(arr - 1), "C") && conf->ceil) ||
        (ft_strequ(*(arr - 1), "F") && conf->floor) ||
        (amount_of(arr, ',') != 2)))
        {
            conf->err = 1;
            return (0);
        }   
    str = ft_strdup("");
    while (arr[++i])
        str = ft_strjoin(ft_strjoin(str, ","), arr[i]);
    clr = ft_split(str, ',');
    i = -1;
    while (clr[++i] && ((color = ft_atoi(clr[i])) || 1))
        if (color < 0 || color > 255 || !ft_strequ(ft_itoa(color), clr[i]))
            conf->err = 1;
    if (conf->err || ((i != 3) && (conf->err = 1)))
        return (0);
    return (trgb(0, ft_atoi(clr[0]), ft_atoi(clr[1]), ft_atoi(clr[2])));
}

static int	check_params(t_conf *conf, char **arr)
{
    if (conf->x && conf->y && conf->no && conf->so && conf->ea &&
        conf->we && conf->sprite && conf->is_ceil && conf->is_floor)
        conf->is_map = 1;
    if (!(ft_strequ(arr[0], "R") || ft_strequ(arr[0], "NO") ||
        ft_strequ(arr[0], "SO") || ft_strequ(arr[0], "EA") ||
        ft_strequ(arr[0], "WE") || ft_strequ(arr[0], "S") ||
        ft_strequ(arr[0], "C") || ft_strequ(arr[0], "F")) && (conf->err = 1))
        return (0);
    return (1);
}

void		parse(const char *line, t_conf *conf)
{
    char **arr;
    char *tmp;
    int i;

    i = -1;
    tmp = ft_strdup(line);
    while (tmp[++i])
        if (tmp[i] == '\t')
            tmp[i] = ' ';
    arr = ft_split(tmp, ' ');
    if (ft_strequ("R", arr[0]))
        check_resolution(conf, arr);
    else if (ft_strequ("NO", arr[0]) || ft_strequ("SO", arr[0]) ||
        ft_strequ("EA", arr[0]) || ft_strequ("WE", arr[0]) ||
        ft_strequ("S", arr[0]))
        check_sprite(conf, arr);
    else if (ft_strequ("C", arr[0]) && (conf->is_ceil = 1))
        conf->ceil = check_color(conf, (arr + 1));
    else if (ft_strequ("F", arr[0]) && (conf->is_floor = 1))
        conf->floor =  check_color(conf, (arr + 1));
    else if (ft_strequ("", arr[0]) || !arr[0])
        return ;
    check_params(conf, arr);
}
