/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:28:48 by minkylee          #+#    #+#             */
/*   Updated: 2023/07/27 18:23:06 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line/get_next_line.h"

int	is_valid_move(t_game *game, int row, int col, int *coin)
{
	if (game->visit[row][col] != '0' || game->map[row][col] == '1')
		return (0);
	else if (game->map[row][col] == 'C')
		*coin += 1;
	else if (game->map[row][col] == 'E' && game->visit[row][col] == '0')
		game->exit = 1;
	return (1);
}

int	where_i_go(int i, int row, int col)
{
	if ((row && i == 0) || (col && i == 2))
		return (-1);
	else if ((row && i == 1) || (col && i == 3))
		return (1);
	else
		return (0);
}

void	dfs(t_game *game, int row, int col, int *coin)
{
	int			i;
	int			next_row;
	int			next_col;

	game->visit[row][col] = '1';
	i = 0;
	while (i < 4)
	{
		next_row = row + where_i_go(i, 1, 0);
		next_col = col + where_i_go(i, 0, 1);
		if (is_valid_move(game, next_row, next_col, coin))
			dfs(game, next_row, next_col, coin);
		i++;
	}
}

int	found_path(t_game *game, t_param *param)
{
	int	coin;

	coin = 0;
	if (param->x == -1 || param->y == -1 || game->cnt < 1)
	{
		free_some(game, param, param->image, 2);
		return (0);
	}
	init_visit(game);
	dfs(game, param->y, param->x, &coin);
	if (coin != game->cnt || game->exit == 0)
	{
		free_some(game, param, param->image, 1);
		return (0);
	}
	return (1);
}

int	found_some(t_game *game, t_param *param)
{
	int	row;

	row = 0;
	while (row < game->height)
	{
		if (!check_exit(game, row) || !check_wall(game, row)
			|| !check_player(game, row, param) || !check_letter(game, row)
			|| (game->width != (int)ft_strlen(game->map[row++])))
		{
			free_some(game, param, param->image, 2);
			return (0);
		}
	}
	if (!found_path(game, param))
		return (0);
	return (1);
}
