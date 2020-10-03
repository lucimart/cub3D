/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 23:22:56 by lucimart          #+#    #+#             */
/*   Updated: 2020/10/03 23:27:54 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libcub3d.h"


static int	check_line(char *line, t_conf *conf)
{
    int i;

    i = -1;
    while (line[++i])
        if (!in_set(line[i], " 012NSEW") && (conf->err = 1))
            return (0);
    return (1);
}

static int	is_part_sorrounded(char **map, int x, int y, char *set)
{
    int check_x;
    int check_y;
    int i;
    int counter;

    counter = 0;
    i = -1;
    check_x = x - 1;
    check_y = y - 1 - 1;
    while (check_x <= x + 1)
    {
        while (++check_y <= y + 1)
            if (check_x < 0 || check_y < 0 ||
                ft_strlen(map[check_x]) - 1 < check_y ||
                in_set(map[check_x][check_y], set))
                return (1);
        check_y = y - 1 - 1;
        if (++counter && (counter == 3) && ((counter = 0) || 1))
            check_x++;
    }
    return (0);
}

static void	check_map(t_conf *conf)
{
    int i;
    int j;

    if (((amount_of(conf->map, 'N') + amount_of(conf->map, 'S') +
        amount_of(conf->map, 'E') + amount_of(conf->map, 'W') != 1)) &&
        (conf->err = 1))
        return ;
    i = -1;
    j = -1;
    while (conf->map[++i])
    {
        while (conf->map[i][++j])
            if (in_set(conf->map[i][j], "02NSEW") &&
                is_part_sorrounded(conf->map, i, j, " ") && (conf->err = 1))
                return ;
        j = -1;
    }
}

void    	parse_map(int fd, char *line, t_conf *conf)
{
    char *tmp;

    if ((get_next_line(fd, &line) <= 0 || (!(*ft_split(line, ' ') == "") &&
        !in_set(*line, " \t1") && !ft_strequ(line, ""))) && (conf->err = 1))
        return ;
    while ((*ft_split(line, ' ') == "") || ft_strchr(line, ' ') ||
        ft_strchr(line, '\t'))
        if ((get_next_line(fd, &line) <= 0) && (conf->err = 1))
            return ;
    tmp = ft_strdup(line);
    while (check_line(line, conf) && (get_next_line(fd, &line) > 0))
        tmp = ft_strjoin((ft_strjoin(tmp, ".")), line);
    if (check_line(line, conf))
        tmp = ft_strjoin((ft_strjoin(tmp, ".")), line);
    conf->map = ft_split(tmp, '.');
    check_map(conf);
}
