/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:36:23 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 20:45:14 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

size_t	ft_strscount(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**copy_map(t_error_ctx *ctx, char **map)
{
	int		i;
	int		len;
	char	**map_copy;

	len = ft_strscount(map);
	map_copy = malloc(sizeof(char *) * (len + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			while (i > 0)
				free(map_copy[i--]);
			free(map_copy);
			throw_err(ERR_MALLOC, ctx);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

int	find_next_zero(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
