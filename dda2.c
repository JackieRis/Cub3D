/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:33:38 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/06 18:45:17 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pick_texel(t_cub *c, t_dda *d, int x)
{
	t_pixel	px;
	double	step;
	double	textpos;
	double	wallx;
	int		textx;

	if (d->side == 0 || d->side == 1)
		wallx = c->p.y + d->pdist * d->rdiry;
	else
		wallx = c->p.x + d->pdist * d->rdirx;
	wallx -= (int)wallx;
	textx = (int)(wallx * (double)c->g.textures[d->side]->w);
	step = 1.0 * c->g.textures[d->side]->h / d->lineh;
	textpos = (d->beg - WIN_H / 2 + d->lineh / 2) * step;
	while (d->beg < d->end)
	{
		px = pick_px(c->g.textures[d->side], textx, (int)textpos);
		draw_px(c->fb, x, d->beg, lerp(px, (t_pixel)FOG, d->fogdist));
		textpos += step;
		d->beg++;
	}
}
