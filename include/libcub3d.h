/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 18:55:31 by lucimart          #+#    #+#             */
/*   Updated: 2020/10/04 18:05:20 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCUB3D_H
# define LIBCUB3D_H
# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>


# ifdef __APPLE__
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
#  define BTN_X 17

# elif defined __unix__
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_ESC 65307
#  define BTN_X 33
# endif

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5

# define NO_EVENT_MASK 0L
# define KEY_PRESS_MASK 1L<<0
# define KEY_RELEASE_MASK 1L<<1
# define BUTTON_PRESS_MASK 1L<<2
# define BUTTON_RELEASE_MASK 1L<<3

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_conf {
	int			x;
	int			y;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	char		*sprite;
	int			is_map;
	int			ceil;
	int			is_ceil;
	int			floor;
	int			is_floor;
	char		**map;
	void		*mlx;
	void        *win;
	int			err;
}				t_conf;


int				trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				get_opposite(int trgb);
int				add_shade(double distance, int trgb);
void            my_mlx_pixel_put(t_data *data, int x, int y, int trgb);
void            close_win(int keycode, t_conf *conf);
int	            is_ext(const char *filename, const char *ext);
int		        is_save_flag(const char *str);
int				amount_of(char **arr, char c);
void			parse(const char *line, t_conf *conf);
void			parse_map(int fd, char *line, t_conf *conf);
#endif