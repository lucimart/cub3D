/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:34:59 by lucimart          #+#    #+#             */
/*   Updated: 2021/02/02 02:03:53 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libcub3d.h"

int		check_ext(const char *filename, const char *ext, t_flags *flags) 
{
	const char *dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename || !ft_strequ(dot, ext))
	{
		err("Invalid file extension (not \'.cub\')", flags);
		return (0);
	}
	return (1);
}

int		is_save(const char *str, t_flags *flags)
{
	if (ft_strequ(str, "--save"))
		return (1);
	err("Invalid flag. Available flags: \'--save\'", flags);
	return (0);	
}

/*
** Initializes each member of the structure but the 'save'
*/
void	map_ini(t_map *map) {
	int i;

	i = -1;
	map->mlx = mlx_init();
	map->win = NULL;
	map->res[0] = 0;
	map->res[1] = 0;
	mlx_get_screen_size(map->mlx, &(map->max_res[0]), &(map->max_res[1]));
	map->no = 0;
	map->so = 0;
	map->ea = 0;
	map->we = 0;
	map->sprite = 0;
	while (++i < 3)
	{
		map->ceil[i] = 0;
		map->floor[i] = 0;
	}
	map->mt = NULL;
}

/*
** Initializes every value of the structure to 0.
*/
void	flags_ini(t_flags *flags)
{
	flags->has_res = 0;
	flags->has_no = 0;
	flags->has_so = 0;
	flags->has_ea = 0;
	flags->has_we = 0;
	flags->has_sprite = 0;
	flags->has_ceil = 0;
	flags->has_floor = 0;
	flags->is_map = 0;
	flags->done = 0;
	flags->valid = 1;
}

/*
** If every 'has' flag is true, then it is effectively done
*/
void	check_done(t_flags *flags)
{
	if (flags->has_res && flags->has_no && flags->has_so && flags->has_ea &&
		flags->has_we && flags->has_ceil && flags->has_floor &&
		flags->has_sprite && flags->has_map)
		flags->done = 1;
}

/*
** free 2D matrix, if not known length set it to -1
** but they'd had to be NULL terminated
*/
void	free_mt(void **ptr, int len)
{
	if (len > 0)
		while (--len >= 0)
		{
			free(ptr[len]);
			ptr[len] = NULL;
		}
	else
		while (*ptr)
		{
			free(*ptr);
			*ptr++ = NULL;
		}
}

/*
** like strlen, but generic (void)
*/
int		mt_len(char **ptr)
{
	int i;

	i = 0;
	while (*(ptr + i))
		i++;
	return (i);
}

void	parse_res_aux(t_flags *flags, t_map *map, char ** arr)
{
	int	i;

	i = -1;
	map->res[0] = ft_atoi(arr[1]);
	map->res[1] = ft_atoi(arr[2]);

	if (ft_strequ(ft_itoa(map->res[0]), arr[1]) &&
		ft_strequ(ft_itoa(map->res[1]), arr[2]))
	{
		while (++i < 2)
			if (map->res[i] > map->max_res[i])
				map->res[i] = map->max_res[i];
		flags->has_res = 1;
		printf("%d\n", map->res[0]);
		printf("%d\n", map->res[1]);
	}

	else
		err("Resolution has wrong arguments, use only numbers", flags);
}

void	parse_res(t_flags *flags, t_map *map, char *line)
{
	char	**arr;
	int		len;

	if (!(flags->has_res))
	{
		arr = ft_split(line, ' ');
		len = mt_len(arr);
		if (arr[0] && ft_strequ(arr[0], "R"))
		{
			if (len == 3)
				parse_res_aux(flags, map, arr);
			else
				err("Incorrect number of arguments for resolution.", flags);
		}
		free_mt((void **)arr, len);
		free(arr);
	}
}

void	parse(int fd, t_map *map, t_flags *flags)
{
	char	*line;
	while (!flags->done && flags->valid && (get_next_line(fd, &line) == 1))
	{
		parse_res(flags, map, line);
		// parse_tex(fd, &flags, map, line);
		// parse_color(fd, &flags, map, line);
		// parse_map(fd, &flags, map, line);
		check_done(flags);
		free(line);
	}
}

void	cub3d(int fd, int save, t_flags *flags)
{
	t_map	map;

	map_ini(&map);
	map.save = save;
	parse(fd, &map, flags);
	//free_data(&map);
}

int		main(int argc, char **argv)
{
	int	save;
	int	fd;
	t_flags flags;
	flags_ini(&flags);

	save = 0;
	if (argc < 2 || argc > 3)
		err("Invalid amount of arguments.", &flags);
	else
	{
		if (argc == 3)
			save = is_save(argv[2], &flags);
		if (check_ext(argv[1], ".cub", &flags))
		{
			if ((fd = open(argv[1], O_RDONLY)) < 0)
				err("Invalid path or read", &flags);
			else
			{
				cub3d(fd, save, &flags);
				close(fd);
			}
		}	
	}
	system("leaks cub3D");
	return(0);
}