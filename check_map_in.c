/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:06:28 by minkylee          #+#    #+#             */
/*   Updated: 2023/07/24 15:19:36 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line/get_next_line.h"

int	check_exit(t_game *game, int row)
{
	int	i;

	i = 0;
	while (i < game->width)
	{
		if (game->map[row][i] == 'E')
		{
			if (game->exit_x == -1 && game->exit_y == -1)
			{
				game->exit_x = i;
				game->exit_y = row;
			}
			else
			{
				ft_printf_s("Too many Exit!\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_wall(t_game *game, int row)
{
	int	i;

	i = 0;
	if (row == 0 || row == game->height - 1)
	{
		while (i < game->width)
		{
			if (game->map[row][i] != '1')
				return (0);
			i++;
		}
	}
	else
	{
		if (game->map[row][0] != '1' || game->map[row][game->width - 1] != '1')
			return (0);
	}
	return (1);
}

int	check_letter(t_game *game, int row)
{
	int	i;

	i = 0;
	while (i < game->width)
	{
		if (game->map[row][i] == 'C')
		game->cnt += 1;
		if (game->map[row][i] != 'C' && game->map[row][i] != '1' &&
			game->map[row][i] != '0' && game->map[row][i] != 'P' &&
			game->map[row][i] != 'E')
			return (0);
		i++;
	}
	return (1);
}

int	check_player(t_game *game, int row, t_param *param)
{
	int	i;

	i = 0;
	while (i < game->width)
	{
		if (game->map[row][i] == 'P')
		{
			if (param->x == -1 && param->y == -1)
			{
				param->x = i;
				param->y = row;
				param->prev_x = param->x;
				param->prev_y = param->y;
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}
