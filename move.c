/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:51:20 by aberneli          #+#    #+#             */
/*   Updated: 2022/05/05 17:10:06 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strafe_player(t_cub *p)
{
	int		**m;

	m = p->m.xy;
	if (p->ev->keys[KEY_D])
	{
		if (!m[(int)(p->p.y)][(int)(p->p.x - p->p.diry * MSPD)])
			p->p.x -= p->p.diry * MSPD;
		if (!m[(int)(p->p.y + p->p.dirx * MSPD)][(int)(p->p.x)])
			p->p.y += p->p.dirx * MSPD;
	}
	if (p->ev->keys[KEY_A])
	{
		if (!m[(int)(p->p.y)][(int)(p->p.x + p->p.diry * MSPD)])
			p->p.x += p->p.diry * MSPD;
		if (!m[(int)(p->p.y - p->p.dirx * MSPD)][(int)(p->p.x)])
			p->p.y -= p->p.dirx * MSPD;
	}
	p->refresh += (p->ev->keys[KEY_D] || p->ev->keys[KEY_A]);
}

void	move_player(t_cub *p)
{
	int		**m;

	m = p->m.xy;
	if (p->ev->keys[KEY_W])
	{
		if (!m[(int)(p->p.y)][(int)(p->p.x + p->p.dirx * MSPD)])
			p->p.x += p->p.dirx * MSPD;
		if (!m[(int)(p->p.y + p->p.diry * MSPD)][(int)(p->p.x)])
			p->p.y += p->p.diry * MSPD;
	}
	if (p->ev->keys[KEY_S])
	{
		if (!m[(int)(p->p.y)][(int)(p->p.x - p->p.dirx * MSPD)])
			p->p.x -= p->p.dirx * MSPD;
		if (!m[(int)(p->p.y - p->p.diry * MSPD)][(int)(p->p.x)])
			p->p.y -= p->p.diry * MSPD;
	}
	p->refresh += (p->ev->keys[KEY_W] || p->ev->keys[KEY_S]);
}

void	orient_player(t_cub *p)
{
	float	oldx;
	float	oldplnx;

	if (p->ev->keys[KEY_ARROW_LEFT])
	{
		oldx = p->p.dirx;
		oldplnx = p->p.planex;
		p->p.dirx = p->p.dirx * cos(-RSPD) - p->p.diry * sin(-RSPD);
		p->p.diry = oldx * sin(-RSPD) + p->p.diry * cos(-RSPD);
		p->p.planex = p->p.planex * cos(-RSPD) - p->p.planey * sin(-RSPD);
		p->p.planey = oldplnx * sin(-RSPD) + p->p.planey * cos(-RSPD);
	}
	if (p->ev->keys[KEY_ARROW_RIGHT])
	{
		oldx = p->p.dirx;
		oldplnx = p->p.planex;
		p->p.dirx = p->p.dirx * cos(RSPD) - p->p.diry * sin(RSPD);
		p->p.diry = oldx * sin(RSPD) + p->p.diry * cos(RSPD);
		p->p.planex = p->p.planex * cos(RSPD) - p->p.planey * sin(RSPD);
		p->p.planey = oldplnx * sin(RSPD) + p->p.planey * cos(RSPD);
	}
	p->refresh += (p->ev->keys[KEY_ARROW_LEFT] || p->ev->keys[KEY_ARROW_RIGHT]);
}
