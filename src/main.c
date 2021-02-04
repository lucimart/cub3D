/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:34:59 by lucimart          #+#    #+#             */
/*   Updated: 2021/02/04 17:59:52 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libcub3d.h"

int		check_ext(const char *file, const char *ext, t_flags *flags, int error)
{
	const char *dot;

	dot = ft_strrchr(file, '.');
	if (!dot || dot == file || !ft_strequ(dot, ext))
	{
		if (error)
			err("Invalid file extension", flags);
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
	int	j;

	i = -1;
	map->mlx = mlx_init();
	map->win = NULL;
	map->res[0] = 0;
	map->res[1] = 0;
	while (++i < 5)
		map->texs[i] = NULL;
	i = -1;
	mlx_get_screen_size(map->mlx, &(map->max_res[0]), &(map->max_res[1]));
	while (++i < 2 && (j = -1))
		while (++j < 3)
			map->sky[i][j] = 0;
	map->mt = NULL;
	map->rows = 0;
	map->cols = -1;
	map->buf = NULL;
	map->buf_rows = 0;
}

/*
** Initializes every value of the structure to 0.
*/
void	flags_ini(t_flags *flags)
{
	int i;

	flags->has_res = 0;
	flags->has_texs = 0;
	flags->has_sky = 0;
	flags->done = 0;
	flags->valid = 1;
	i = -1;
	while (++i < 2)
		flags->sky_def[i] = 0;
}

/*
** If every 'has' flag is true, then it is effectively done
*/
void	check_done(t_flags *flags)
{
	if (flags->has_res && (flags->has_sky == 2) &&
		(flags->has_texs == 5) && flags->has_map)
		flags->done = 1;
}

/*
** free 2D matrix, if not known length set it to -1
** but they'd had to be NULL terminated
*/
void	free_mt(char **ptr, int len)
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
	free(ptr);
	ptr = NULL;
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

/*
** Given a str that we want to see if its numeric val
** is truly equal to the str, ex: "123" = 123. TRUE
** but ex: "123a45" = 123. FALSE
*/
int		cmp_atoi_itoa(char *str)
{
	int		atoi;
	char	*itoa;
	int		ret;

	atoi = ft_atoi(str);
	itoa = ft_itoa(atoi);
	ret = ft_strequ(str, itoa);
	free(itoa);
	return (ret);
}

int		cmp_and_ret(int i, int j, int bigger)
{
	int	ret;

	if (bigger)
		ret = (i >= j) ? i : j;
	else
		ret = (i >= j) ? j : i;
	return (ret);
}

void	parse_res_aux(t_flags *flags, t_map *map, char **arr)
{
	map->res[0] = ft_atoi(arr[1]);
	map->res[1] = ft_atoi(arr[2]);

	if (cmp_atoi_itoa(arr[1]) && cmp_atoi_itoa(arr[2]) &&
		map->res[0] > 0 && map->res[1] > 0)
	{
		map->res[0] = cmp_and_ret(map->res[0], map->max_res[0], 1);
		map->res[1] = cmp_and_ret(map->res[1], map->max_res[1], 1);
		flags->has_res = 1;
	}
	else
		err("Resolution has wrong args, use only positive numbers", flags);
}

void	parse_res(t_flags *flags, t_map *map, char *line)
{
	char	**arr;
	int		len;

	if (!(flags->has_res) && flags->valid)
	{
		arr = ft_split(line, ' ');
		len = mt_len(arr);
		if (arr[0] && ft_strequ(arr[0], "R"))
		{
			if (len == 3 && !(map->res[0]))
				parse_res_aux(flags, map, arr);
			else if (len == 3 && map->res[0])
				err("Resolution already defined", flags);
			else
				err("Incorrect number of arguments for resolution.", flags);
		}
		free_mt(arr, len);
	}
}

int		is_tex(char *str)
{
	int	ret;

	if (ft_strequ(str, "NO"))
		ret = 1;
	else if (ft_strequ(str, "SO"))
		ret = 2;
	else if (ft_strequ(str, "EA"))
		ret = 3;
	else if (ft_strequ(str, "WE"))
		ret = 4;
	else if (ft_strequ(str, "S"))
		ret = 5;
	else
		ret = 0;
	return (ret);
	
}

void	parse_tex_aux(t_flags *flags, t_map *map, char **arr, int is_tex)
{
	int	tex;
	int	fd;

	tex = is_tex - 1;
	if (!map->texs[tex])
	{
		if (!(check_ext(arr[1], ".xpm", flags, 0) ||
			check_ext(arr[1], ".png", flags, 0)))
			err("Texture has invalid file extension", flags);
		else
		{
			map->texs[tex] = ft_strdup(arr[1]);
			fd = open(map->texs[tex], O_RDONLY);
			if (fd >= 0)
				close(fd);
			else
				err("Texture file does not exist in given path.", flags);
			flags->has_texs++;
		}
	}
	else
		err("Texture already defined", flags);
}

void	parse_tex(t_flags *flags, t_map *map, char *line)
{
	char	**arr;
	int		len;

	if (flags->has_texs != 5 && flags->valid)
	{
		arr = ft_split(line, ' ');
		len = mt_len(arr);
		if (arr[0] && is_tex(arr[0]))
		{
			if (len == 2)
				parse_tex_aux(flags, map, arr, is_tex(arr[0]));
			else
				err("Incorrect number of arguments for texture.", flags);
		}
		free_mt(arr, len);
	}	
}

int		is_sky(char *str)
{
	int	ret;

	if (ft_strequ(str, "C"))
		ret = 1;
	else if (ft_strequ(str, "F"))
		ret = 2;
	else
		ret = 0;
	return (ret);
}

int		rgb_validator(char *r, char *g, char *b)
{
	int rgb[3];
	int i;

	i = -1;
	rgb[0] = ft_atoi(r);
	rgb[1] = ft_atoi(g);
	rgb[2] = ft_atoi(b);
	if (!(cmp_atoi_itoa(r)) || !(cmp_atoi_itoa(g)) ||
		!(cmp_atoi_itoa(b)))
		return (0);
	while (++i < 3)
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
	return (1);
}

void	parse_sky_aux(t_flags *flags, t_map *map, char **rgb, int is_sky)
{
	int	sky;
	int	i;

	i = -1;
	sky = is_sky - 1;
	if (!flags->sky_def[sky])
	{
		if (!(rgb_validator(rgb[0], rgb[1], rgb[2])))
			err("Invalid color", flags);
		else
		{
			while (++i < 3)
				map->sky[sky][i] = ft_atoi(rgb[i]);
			flags->sky_def[sky] = 1;
			flags->has_sky++;
		}
	}
	else
		err("Ceil/Floor already defined", flags);
}

char	*arr_join(char **arr)
{
	char	*str;
	int		len;
	int		i;

	str = ft_strdup("");
	len = mt_len(arr);
	i = -1;
	while (++i < len)
		ft_strlcat(str, arr[i], ft_strlen(arr[i]) + 1);
	return (str);
}

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

char	**parse_sky_field(char **arr, int len, t_flags *flags)
{
	char	**new;
	char	**ret;
	char *str;
	int i;
	int length;

	if (!(new = (char **)malloc(sizeof(char *) * (len - 1))))
		return (NULL);
	i = -1;
	while (i++ < (len - 1))
		new[i] = ft_strdup(arr[i + 1]);
	if (amount_of(arr, ',') != 2)
	{
		err("Invalid parameter for ceil/floor", flags);
		return (NULL);
	}
	str = arr_join(new);
	length = mt_len(new);
	free_mt(new, length);
	ret = ft_split(str, ',');
	free(str);
	return (ret);
}

void	parse_sky(t_flags *flags, t_map *map, char *line)
{
	char	**arr;
	int		len;
	char	**new;

	if (flags->has_sky != 2 && flags->valid)
	{
		arr = ft_split(line, ' ');
		len = mt_len(arr);
		if (arr[0] && is_sky(arr[0]))
		{
			new = parse_sky_field(arr, len, flags);
			if (mt_len(new) == 3 && flags->valid)
				parse_sky_aux(flags, map, new, is_sky(arr[0]));
			else
				err("Incorrect number of arguments for ceiling/floor.", flags);
			free_mt(new, mt_len(new));
		}
		free_mt(arr, mt_len(arr));
	}	
}

int		only_map_left(t_flags *flags)
{
	int ret;

	ret = 0;
	if (flags->has_res && (flags->has_sky == 2) &&
		(flags->has_texs == 5))
		ret = 1;
	return (ret);
}

char	**read_map(t_map *map, int row)
{
	char	**ret;
	int		i;
	int		j;
	int		k;

	map->rows = map->buf_rows - row + 1;
	ret = (char **)ft_calloc(map->rows + 1, sizeof(char *));
	ret[map->rows] = NULL;
	i = row - 1;
	while (map->buf[++i] && i <= map->buf_rows)
		map->cols = map->cols >= (int)ft_strlen(map->buf[i]) ? map->cols :
					ft_strlen(map->buf[i]);
	i = -1;
	while (++i < map->rows)
		ret[i] = (char *)ft_calloc(map->cols, sizeof(char));
	i = row - 1;
	j = -1;
	k = -1;
	while (++i < (map->buf_rows + 1) && ++k < map->rows && (j = -1))
		while (++j < map->cols)
		{
			if (j < (int)ft_strlen(map->buf[i]))
				ret[k][j] = map->buf[i][j];
			else
				ret[k][j] = ' ';
		}
	return (ret);
}

int		is_part_sorrounded(char **map, int x, int y, char *set)
{
    int check_x;
    int check_y;
    int counter;

    counter = 0;
    check_x = x - 1;
    check_y = y - 1 - 1;
    while (check_x <= x + 1)
    {
        while (++check_y <= y + 1)
            if (check_x < 0 || check_y < 0 ||
                check_y > (int)ft_strlen(map[check_x]) - 1 ||
                in_set(map[check_x][check_y], set))
                return (1);
        check_y = y - 1 - 1;
        if (++counter && (counter == 3) && ((counter = 0) || 1))
            check_x++;
    }
    return (0);
}

void	validate_map(t_map *map, t_flags *flags)
{
	int	i;
	int	j;

	if (amount_of(map->mt, 'N') + amount_of(map->mt, 'S') +
		amount_of(map->mt, 'E') + amount_of(map->mt, 'W') != 1)
		flags->valid = 0;
	i = -1;
	while (++i < map->rows && (j = -1))
		while (++j)
			if (!(in_set(map->mt[i][j], " 012NSEW")) ||
				(in_set(map->mt[i][j], "02NSEW") &&
				is_part_sorrounded(map->mt, i, j, " ")))
				flags->valid = 0;
}

void	parse_map(t_flags *flags, t_map *map, int cur_row)
{
	if (only_map_left(flags) && flags->valid)
	{
		map->mt = read_map(map, ++cur_row);
		validate_map(map, flags);
		if (flags->valid)
			flags->has_map = 1;
	}
}

void	parse(t_map *map, t_flags *flags)
{
	int	i;

	i = -1;
	while (!flags->done && flags->valid)
	{
		parse_res(flags, map, map->buf[++i]);
		parse_tex(flags, map, map->buf[i]);
		parse_sky(flags, map, map->buf[i]);
		parse_map(flags, map, i);
		check_done(flags);
	}
}

void	free_data(t_map *map)
{
	int i;

	i = -1;
	while (++i < 5)
		if (map->texs[i])
			free(map->texs[i]);
	free_mt(map->mt, map->rows);
	free_mt(map->buf, map->buf_rows + 1);
}

void	map_buffer(t_map *map, int *fd, char *path)
{
	int i;
	char *line;

	i = 0;
	while (++i && (get_next_line(*fd, &line) == 1))
		free(line);
	free(line);
	i--;
	close(*fd);
	*fd = open(path, O_RDONLY);
	map->buf = (char **)ft_calloc(i, sizeof(char *));
	map->buf_rows = i;
	i = -1;
	while ((get_next_line(*fd, &line) == 1))
		map->buf[++i] = line;
	map->buf[++i] = line;
	close(*fd);
}

void	cub3d(int *fd, int save, t_flags *flags, char *path)
{
	t_map	map;

	map_ini(&map);
	map_buffer(&map, fd, path);
	map.save = save;
	parse(&map, flags);
	free_data(&map);
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
		if (check_ext(argv[1], ".cub", &flags, 0))
		{
			if ((fd = open(argv[1], O_RDONLY)) < 0)
				err("Invalid path or read", &flags);
			else
				cub3d(&fd, save, &flags, argv[1]);
		}	
	}
	system("leaks cub3D");
	return(0);
}