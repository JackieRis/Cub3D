/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:25:04 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/06 18:44:36 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	quit_hook(void	*p)
{
	t_cub	*c;

	c = p;
	clear_cub(c);
	exit (0);
	return (0);
}

static void	bg_colors(t_cub *c)
{
	float	t;
	int		y;
	int		x;

	y = 0;
	t = 0.0f;
	while (y < c->fb->h)
	{
		x = 0;
		while (x < c->fb->w)
		{
			if (y < c->fb->h / 2)
				draw_px(c->fb, x, y, lerp(c->g.ccolor, (t_pixel)FOG, t));
			else
				draw_px(c->fb, x, y, lerp(c->g.fcolor, (t_pixel)FOG, t));
			x++;
		}
		if (y < c->fb->h / 2)
			t += 1.0f / (float)(c->fb->h / 2);
		else
			t -= 1.0f / (float)(c->fb->h / 2);
		y++;
	}
}

int	loop_hook(void *p)
{
	t_img	*tmp;
	t_cub	*c;

	c = p;
	if (c->ev->keys[KEY_ESCAPE])
	{
		clear_cub(c);
		exit(0);
	}
	strafe_player(c);
	move_player(c);
	orient_player(c);
	if (c->refresh)
	{
		bg_colors(c);
		dda(c);
		mlx_put_image_to_window(c->mlx, c->mlx_win, c->fb->img, 0, 0);
		tmp = c->fb;
		c->fb = c->fb_swap;
		c->fb_swap = tmp;
		c->refresh = 0;
	}
	return (0);
}
