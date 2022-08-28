/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:29:20 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/05 16:17:46 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_str(char *s1, char s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2)
			return (1);
		i++;
	}
	return (-1);
}

int	print_error(char const *error, void *ptr)
{
	free(ptr);
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
	return (-1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
				str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (!(str[i] > 47 && str[i] < 58))
		return (-1);
	while (str[i] > 47 && str[i] < 58)
	{
		r = r * 10 + (str[i] - '0');
		if (r > 255)
			return (-1);
		i++;
	}
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
				str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i])
		return (-1);
	return (r);
}
