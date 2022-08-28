/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:58:12 by aberneli          #+#    #+#             */
/*   Updated: 2022/05/06 14:53:16 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_border(t_cub *c)
{
	int	i;

	i = 0;
	while (i < c->m.w)
	{
		if (c->m.xy[0][i] != 1 || c->m.xy[c->m.h - 1][i] != 1)
			return (print_error(ERR_WRONG_BORDER, NULL));
		i++;
	}
	i = 0;
	while (i < c->m.h)
	{
		if (c->m.xy[i][0] != 1 || c->m.xy[i][c->m.w - 1] != 1)
			return (print_error(ERR_WRONG_BORDER, NULL));
		i++;
	}
	return (0);
}

static int	extract(char *line, char *id, char **data, const char *err_msg)
{
	if (ft_strncmp(id, line, ft_strlen(id)) == 0)
	{
		if (*data)
			return (print_error(err_msg, line));
		*data = ft_skipstrdup(line);
		return (1);
	}
	return (0);
}

int	check_cardinals(t_data *d, char *line)
{
	int	res;

	res = extract(line, "NO ", &d->no, ERR_NO_REDEF);
	if (res != 0)
		return (res);
	res = extract(line, "SO ", &d->so, ERR_SO_REDEF);
	if (res != 0)
		return (res);
	res = extract(line, "WE ", &d->we, ERR_WE_REDEF);
	if (res != 0)
		return (res);
	res = extract(line, "EA ", &d->ea, ERR_EA_REDEF);
	if (res != 0)
		return (res);
	res = extract(line, "F ", &d->tmpf, ERR_FLOOR_REDEF);
	if (res != 0)
		return (res);
	res = extract(line, "C ", &d->tmpc, ERR_CEIL_REDEF);
	if (res != 0)
		return (res);
	return (0);
}

int	check_garbage(char *line)
{
	int	i;

	if (line[0] == '\n')
		return (0);
	i = 1;
	while (line[i] && line[i] != '\n')
	{
		if (validate_str("01 ", line[i]) < 0)
			return (print_error("Line with garbage information.\n", line));
		i++;
	}
	return (0);
}
