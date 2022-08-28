/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:09:45 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/06 18:51:00 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	help_me_stepx(t_cub *c, t_dda *d)
{
	if (d->rdirx < 0)
	{	
		d->stepx = -1;
		d->sdistx = (c->p.x - d->mapx) * d->ddistx;
	}
	else
	{	
		d->stepx = 1;
		d->sdistx = (d->mapx + 1.0 - c->p.x) * d->ddistx;
	}
	if (d->rdiry < 0)
	{	
		d->stepy = -1;
		d->sdisty = (c->p.y - d->mapy) * d->ddisty;
	}
	else
	{	
		d->stepy = 1;
		d->sdisty = (d->mapy + 1.0 - c->p.y) * d->ddisty;
	}
}

static void	dda_init(t_cub *c, t_dda *d)
{
	d->rdirx = c->p.dirx + c->p.planex * d->camx;
	d->rdiry = c->p.diry + c->p.planey * d->camx;
	d->mapx = (int)c->p.x;
	d->mapy = (int)c->p.y;
	d->ddistx = 1e30;
	d->ddisty = 1e30;
	if (d->rdirx != 0)
		d->ddistx = fabs(1 / d->rdirx);
	if (d->rdiry != 0)
		d->ddisty = fabs(1 / d->rdiry);
	d->hit = 0;
	d->side = 0;
	help_me_stepx(c, d);
}

static void	rtx_on(t_cub *c, t_dda *d)
{
	while (!d->hit)
	{
		if (d->sdistx < d->sdisty)
		{
			d->sdistx += d->ddistx;
			d->mapx += d->stepx;
			d->side = (d->stepx >= 0);
		}
		else
		{
			d->sdisty += d->ddisty;
			d->mapy += d->stepy;
			d->side = (d->stepy >= 0) + 2;
		}
		if (c->m.xy[d->mapy][d->mapx] > 0)
			d->hit = c->m.xy[d->mapy][d->mapx];
	}
	if (d->side == 0 || d->side == 1)
		d->pdist = d->sdistx - d->ddistx;
	else
		d->pdist = d->sdisty - d->ddisty;
}

static void	line_stripe(t_cub *c, t_dda *d, int x)
{
	d->lineh = WIN_H / d->pdist;
	d->beg = WIN_H / 2 - d->lineh / 2;
	if (d->beg < 0)
		d->beg = 0;
	d->end = WIN_H / 2 + d->lineh / 2;
	if (d->end >= WIN_H)
		d->end = WIN_H - 1;
	d->fogdist = d->pdist / 12.0;
	if (d->fogdist > 1.0)
		d->fogdist = 1.0;
	pick_texel(c, d, x);
}

void	dda(t_cub *c)
{
	t_dda	d;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		d.camx = (x + x) / (double)WIN_W - 1;
		dda_init(c, &d);
		rtx_on(c, &d);
		line_stripe(c, &d, x);
		x++;
	}
}
