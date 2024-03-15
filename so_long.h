/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:29:08 by minkylee          #+#    #+#             */
/*   Updated: 2023/07/27 18:22:29 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>

# define KEY_ESC        53
# define KEY_W          13
# define KEY_A          0
# define KEY_S          1
# define KEY_D          2
# define KEY_X_BUTTON	17

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		height;
	int		width;
	int		walk_cnt;
	char	**visit;
	int		exit_x;
	int		exit_y;
	int		exit;
	int		coin;
	int		cnt;
}			t_game;

typedef struct s_image
{
	void	*img_grass;
	void	*img_player;
	void	*img_coin;
	void	*img_hill;
	void	*img_exit;
}		t_image;

typedef struct s_param
{
	int		x;
	int		y;
	int		prev_x;
	int		prev_y;
	t_game	*game;
	t_image	*image;
}			t_param;

void	draw_map(t_param *param, t_game *game);
int		parse_map(int fd, t_game *game, int count);
int		handle_key_event(int keycode, t_param *param);
int		is_valid_param(t_param *param, t_game *game, int x, int y);
void	update_game(t_game *game, t_param *param);
void	init_visit(t_game *game);
int		is_valid_move(t_game *game, int row, int col, int *coin);
int		check_player(t_game *game, int row, t_param *param);
int		check_letter(t_game *game, int row);
int		where_i_go(int i, int row, int col);
void	dfs(t_game *game, int row, int col, int *coin);
int		check_wall(t_game *game, int row);
int		found_some(t_game *game, t_param *param);
int		check_exit(t_game *game, int row);
void	init_structure(t_game *game, t_param *param, t_image *image);
void	init_image(t_image *image, t_game *game);
int		count_row(char *file);
int		valid_extensions(char *file);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		join_map(char *line, int *col, t_game *game, int row);
void	ft_printf_s(char *s);
void	ft_printf_d(long long n);
void	print_image(t_param *param, char c, int wid, int hei);
int		end_game(t_param *param);
void	start_game(t_game *game, t_param *param, t_image *image);
int		is_valid_game(char *file, t_game *game, t_param *param, t_image *image);
void	free_some(t_game *game, t_param *param, t_image *image, int flag);
int		found_path(t_game *game, t_param *param);

#endif