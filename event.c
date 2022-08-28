/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:10:05 by aberneli          #+#    #+#             */
/*   Updated: 2022/05/05 16:46:03 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_input.h"

#include <stdlib.h>

t_mod	key_to_mod(t_keys key)
{
	if (key == KEY_LSHIFT)
		return (MOD_LSHIFT);
	if (key == KEY_LCTRL)
		return (MOD_LCTRL);
	if (key == KEY_LALT)
		return (MOD_LALT);
	if (key == KEY_RALT)
		return (MOD_RALT);
	if (key == KEY_RCTRL)
		return (MOD_RCTRL);
	if (key == KEY_RSHIFT)
		return (MOD_RSHIFT);
	return (0);
}

void	release_events(t_event *ev)
{
	if (!ev)
		return ;
	free(ev->keys);
	free(ev->buttons);
	free(ev->mods);
	free(ev);
}

static void	ft_bzero(void *a, size_t size)
{
	unsigned char	*p;
	size_t			i;

	p = a;
	i = 0;
	while (i < size)
		p[i++] = 0;
}

t_event	*register_events(void *mlx_win)
{
	t_event	*ev;

	ev = malloc(sizeof(t_event));
	if (!ev)
		return (NULL);
	ft_bzero(ev, sizeof(t_event));
	ev->keys = malloc(sizeof(t_keys) * MAX_KEYS);
	ev->buttons = malloc(sizeof(t_mbutton) * MAX_BUTTONS);
	ev->mods = malloc(sizeof(t_mod) * MOD_KEYS);
	if (!ev->keys || !ev->buttons || !ev->mods)
	{
		release_events(ev);
		return (NULL);
	}
	ft_bzero(ev->keys, sizeof(t_keys) * MAX_KEYS);
	ft_bzero(ev->buttons, sizeof(t_mbutton) * MAX_BUTTONS);
	ft_bzero(ev->mods, sizeof(t_mod) * MOD_KEYS);
	mlx_hook(mlx_win, 2, 0, ehook_keydown, ev);
	mlx_hook(mlx_win, 3, 0, ehook_keyup, ev);
	mlx_hook(mlx_win, 4, 0, ehook_mousedown, ev);
	mlx_hook(mlx_win, 5, 0, ehook_mouseup, ev);
	mlx_hook(mlx_win, 6, 0, ehook_mousemove, ev);
	return (ev);
}
