/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:52:14 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/23 14:53:34 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_close(t_game *game)
{
	clean_game(game);
	exit(0);
}

int	key_press(int keysym, t_game *game)
{
	if (keysym == ESCAPE)
		ft_close(game);
	if (keysym == S)
		game->player.move_down = TRUE;
	if (keysym == W)
		game->player.move_up = TRUE;
	if (keysym == A)
		game->player.move_left = TRUE;
	if (keysym == D)
		game->player.move_right = TRUE;
	if (keysym == LEFT)
		game->player.left_rotate = TRUE;
	if (keysym == RIGHT)
		game->player.right_rotate = TRUE;
	if (keysym == UP)
		game->player.run = TRUE;
	return (0);
}

int	key_release(int keysym, t_player *player)
{
	if (keysym == S)
		player->move_down = FALSE;
	if (keysym == W)
		player->move_up = FALSE;
	if (keysym == A)
		player->move_left = FALSE;
	if (keysym == D)
		player->move_right = FALSE;
	if (keysym == LEFT)
		player->left_rotate = FALSE;
	if (keysym == RIGHT)
		player->right_rotate = FALSE;
	if (keysym == UP)
		player->run = FALSE;
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, key_release, &game->player);
	mlx_hook(game->win_ptr, 17, 1L << 17, ft_close, game);
}
