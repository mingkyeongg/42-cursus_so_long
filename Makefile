# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/15 22:16:34 by minkylee          #+#    #+#              #
#    Updated: 2023/07/27 18:18:19 by minkylee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c\
		main.c\
		move_player.c\
		check_map.c\
		check_map_in.c\
		initalize.c\
		check_argv.c\
		print_some.c\
		make_map.c\

OBJS = $(SRCS:.c=.o)

%.o:%.c so_long.h
	cc -Wall -Wextra -Werror -c $< -o $@

$(NAME) : 	$(OBJS)
			make -C ./mlx/
			cc -o so_long $(OBJS) -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re