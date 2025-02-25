/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:44:30 by albernar          #+#    #+#             */
/*   Updated: 2025/02/20 15:55:21 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

char	*ft_strnjoin(char *s1, char *s2, int len, int flag)
{
	char	*res;
	char	*orig_s2;
	int		i;

	orig_s2 = s2;
	res = malloc(sizeof(char) * (ft_strlen(s1) + len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && *(s1 + i))
	{
		*(res + i) = *(s1 + i);
		i++;
	}
	while (s2 && *s2 && len--)
		*(res + i++) = *s2++;
	*(res + i) = 0;
	if (flag == 1)
		free(s1);
	else if (flag == 2)
		free(orig_s2);
	return (res);
}
