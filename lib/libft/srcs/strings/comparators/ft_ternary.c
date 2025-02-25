/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ternary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:28:57 by albernar          #+#    #+#             */
/*   Updated: 2025/02/09 20:31:50 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ternaryint(int condition, int true_value, int false_value)
{
	if (condition)
		return (true_value);
	return (false_value);
}

const char	*ft_ternarystring(int condition,
	char *true_value, char *false_value)
{
	if (condition)
		return (true_value);
	return (false_value);
}
