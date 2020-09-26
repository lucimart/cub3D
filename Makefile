# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/24 23:50:14 by lucimart          #+#    #+#              #
#    Updated: 2020/09/27 01:06:08 by lucimart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $@ stands for the target
# $< stands for the first dependency
# $^ is similar to $<, but $^ stands for all the dependencies 
# while $< will only get the first one.

NAME =			cub3D
MLX_LINUX =		-Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MLX_LINUX_OBJ =	-I/usr/include -Imlx_linux -O3
CC =			gcc
CFLAGS =		-g -Wall -Werror -Wextra
LIBFT_DIR =		./libft/
LIBFT =			$(LIBFT_DIR)libft.a
HEADERS_DIR = 	-I ./includes
REG_SRCS =		ft_cub3d.c
BONUS_SRCS =

# ifdef does not expand variable references; it just sees if something is defined at all
# You can text replace at the end of each space seperated word using $(var:a=b)
ifdef WITH_BONUS
OBJS = $(REG_SRCS:.c=.o)  -$(BONUS_SRCS:.c=.o) 
else
OBJS = $(REG_SRCS:.c=.o) 
endif

# The all rule itself has no special meaning.
# Make simply runs the first rule when no rule is specified.
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(MLX) -o $@ $^

$(LIBFT):
	$(MAKE) -s bonus -C $(LIBFT_DIR)
# If the object file doesn’t exist or if the source file is newer
# than the object file, the contents of the rule will be executed.
%.o: %.c
	@$(CC) -c $(CFLAGS) $(HEADERS_DIR) $(MLX_LINUX_OBJ) -o $@ $<

# @ makes it silent.
# - in front of the command makes sure that make ignores a non-zero return code
clean:
	$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

fclean: clean
	$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

# Instead of having fclean and all as dependencies we will recursively
# call make twice. The $(MAKE) rule will expand to a make with all of
# the flags used to call the parent make pre-set.
re:
	$(MAKE) fclean
	$(MAKE) all

bonus:
	$(MAKE) WITH_BONUS=1 all
#.PHONY line means that all of these rules should be treated like commands, not
# outputs. So even if there exists a file called clean, clean will still run.
.PHONY: all clean fclean re bonus libft

# https://noahloomans.com/tutorials/makefile/
# https://makefiletutorial.com/
# https://www.gnu.org/software/make/manual/make.html