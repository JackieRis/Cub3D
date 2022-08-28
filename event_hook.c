/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:43:47 by aberneli          #+#    #+#             */
/*   Updated: 2022/01/23 07:11:56 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_input.h"

int	ehook_keydown(int key, void *e)
{
	t_event	*ev;

	ev = e;
	ev->keys[key] = 1;
	if (key_to_mod(key) != 0)
		ev->mods[key_to_mod(key)] = 1;
	return (1);
}

int	ehook_keyup(int key, void *e)
{
	t_event	*ev;

	ev = e;
	ev->keys[key] = 0;
	if (key_to_mod(key) != 0)
		ev->mods[key_to_mod(key)] = 0;
	return (1);
}

int	ehook_mousedown(int button, int x, int y, void *e)
{
	t_event	*ev;

	(void)x;
	(void)y;
	ev = e;
	ev->buttons[button] = 1;
	return (1);
}

int	ehook_mouseup(int button, int x, int y, void *e)
{
	t_event	*ev;

	(void)x;
	(void)y;
	ev = e;
	ev->buttons[button] = 0;
	return (1);
}

int	ehook_mousemove(int x, int y, void *e)
{
	t_event	*ev;

	ev = e;
	ev->rx = ev->mx;
	ev->ry = ev->my;
	ev->mx = x;
	ev->my = y;
	return (1);
}
