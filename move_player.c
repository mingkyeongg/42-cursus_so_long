/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:36:19 by minkylee          #+#    #+#             */
/*   Updated: 2023/07/27 15:46:08 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "so_long.h"

void	print_image(t_param *param, char c, int wid, int hei)
{
	if (c == 'E')
		mlx_put_image_to_window(param->game->mlx, param->game->win, \
			param->image->img_exit, wid * 64, hei * 64);
	else if (c == 'C')
		mlx_put_image_to_window(param->game->mlx, param->game->win, \
			param->image->img_coin, wid * 64, hei * 64);
	else if (c == 'P')
		mlx_put_image_to_window(param->game->mlx, param->game->win, \
			param->image->img_player, wid * 64, hei * 64);
	else if (c == '1')
		mlx_put_image_to_window(param->game->mlx, param->game->win, \
			param->image->img_hill, wid * 64, hei * 64);
	else
		mlx_put_image_to_window(param->game->mlx, param->game->win, \
			param->image->img_grass, wid * 64, hei * 64);
}

int	end_game(t_param *param)
{
	mlx_destroy_window(param->game->mlx, param->game->win);
	free_some(param->game, param, param->image, 1);
	exit(0);
}

void	update_game(t_game *game, t_param *param)
{
	if (game->map[param->prev_y][param->prev_x] != 'E')
	{
		print_image(param, '0', param->prev_x, param->prev_y);
		print_image(param, 'P', param->x, param->y);
	}
	else if (game->map[param->prev_y][param->prev_x] == 'E')
	{
		print_image(param, '0', param->prev_x, param->prev_y);
		print_image(param, 'E', param->prev_x, param->prev_y);
		print_image(param, 'P', param->x, param->y);
	}
	if (game->map[param->y][param->x] == 'C' &&
		game->visit[param->y][param->x] == '0')
	{
		game->coin += 1;
		game->visit[param->y][param->x] = '1';
	}
	if (game->map[param->y][param->x] == 'E' && game->coin == game->cnt)
	{
		ft_printf_s("Congratulations! You cleared the game.\n");
		end_game(param);
	}
	ft_printf_d(game->walk_cnt);
	param->prev_x = param->x;
	param->prev_y = param->y;
}

int	is_valid_param(t_param *param, t_game *game, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = param->x + x;
	new_y = param->y + y;
	if (game->map[new_y][new_x] == '1')
		return (0);
	game->walk_cnt++;
	return (1);
}

int	handle_key_event(int keycode, t_param *param)
{
	if (keycode == KEY_ESC)
		end_game(param);
	else if (keycode == KEY_A)
	{
		if (is_valid_param(param, param->game, -1, 0))
			param->x -= 1;
	}
	else if (keycode == KEY_D)
	{
		if (is_valid_param(param, param->game, 1, 0))
			param->x += 1;
	}
	else if (keycode == KEY_S)
	{
		if (is_valid_param(param, param->game, 0, 1))
			param->y += 1;
	}
	else if (keycode == KEY_W)
	{
		if (is_valid_param(param, param->game, 0, -1))
			param->y -= 1;
	}
	update_game(param->game, param);
	return (0);
}
