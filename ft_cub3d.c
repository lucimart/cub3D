/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 18:59:28 by lucimart          #+#    #+#             */
/*   Updated: 2020/10/04 01:45:14 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libcub3d.h"



void            conf_ini(t_conf *conf)
{
	conf->x = 0;
	conf->y = 0;
	conf->no = 0;
	conf->so = 0;
	conf->ea = 0;
	conf->we = 0;
	conf->sprite = 0;
	conf->is_map = 0;
	conf->ceil = 0;
    conf->is_ceil = 0;
	conf->floor = 0;
    conf->is_floor = 0;
    conf->err = 0;
    conf->map = 0;
    conf->mlx = mlx_init();
}

void            pre_game(t_conf *conf, int argc, char **argv)
{
    int fd;
    char *line;
    conf_ini(conf);
    if (argc < 2 || argc > 3)
        ft_putstr("Error\nInvalid amount of arguments.");
    else if (argc == 2 && !is_ext(argv[1], ".cub"))
        conf->err = 1;
    else if (argc == 3 && !(is_ext(argv[1], ".cub") && is_save_flag(argv[1])))
        conf->err = 1;
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        ft_putstr("Error\nThe file does not exist.");
    else
    {
        while (!conf->is_map && !conf->err && (get_next_line(fd, &line) >= 0))
            parse(line, conf);
        if (conf->is_map && !conf->err)
            parse_map(fd, line, conf);
        if (conf->err)
            ft_putstr("Error\nThere was an error while parsing the file");
    } 
    close(fd);
}

int             main(int argc, char **argv)
{   
    t_conf conf;

    pre_game(&conf, argc, argv);
    return (0);
} 