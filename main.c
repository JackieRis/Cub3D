/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:12:02 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/07 09:35:04 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>

static int	check_extension(char *file)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i + j] == CUB_EXTENSION[j])
		{
			j++;
			if (file[i + j] == '\0' && CUB_EXTENSION[j] == '\0')
				return (0);
		}
		i++;
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	t_cub	*c;

	if (argc < 2)
		return (print_error(ERR_NO_FILE, NULL));
	if (argc > 2)
		return (print_error(ERR_TOO_MANY_ARGS, NULL));
	if (check_extension(argv[1]) < 0)
		return (print_error(ERR_NOT_CUB, NULL));
	c = malloc(sizeof(t_cub));
	if (!c)
		return (print_error(ERR_ALLOC, NULL));
	if (init_cub(c, argv[1]) < 0)
	{
		clear_cub(c);
		return (-1);
	}
	return (0);
}
