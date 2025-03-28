/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_uint8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:48:36 by albernar          #+#    #+#             */
/*   Updated: 2025/03/28 09:39:40 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

static void	mlxcolor_memset_align(void *s, uint32_t c, size_t n)
{
	uint64_t	c64;
	size_t		k;

	c64 = c | ((uint64_t)c << 32);
	k = 24 + ((uintptr_t)s & 4);
	s += k;
	n -= k;
	while (n >= 32)
	{
		*(uint64_t *)(s + 0) = c64;
		*(uint64_t *)(s + 8) = c64;
		*(uint64_t *)(s + 16) = c64;
		*(uint64_t *)(s + 24) = c64;
		s += 32;
		n -= 32;
	}
}

static void	mlxcolor_memset_prepare(void *s, uint32_t c, size_t n)
{
	uint32_t	c32;

	n &= -4;
	c32 = c;
	*(uint32_t *)(s + 0) = c32;
	*(uint32_t *)(s + n - 4) = c32;
	if (n <= 8)
		return ;
	*(uint32_t *)(s + 4) = c32;
	*(uint32_t *)(s + 8) = c32;
	*(uint32_t *)(s + n - 12) = c32;
	*(uint32_t *)(s + n - 8) = c32;
	if (n <= 24)
		return ;
	*(uint32_t *)(s + 12) = c32;
	*(uint32_t *)(s + 16) = c32;
	*(uint32_t *)(s + 20) = c32;
	*(uint32_t *)(s + 24) = c32;
	*(uint32_t *)(s + n - 28) = c32;
	*(uint32_t *)(s + n - 24) = c32;
	*(uint32_t *)(s + n - 20) = c32;
	*(uint32_t *)(s + n - 16) = c32;
	mlxcolor_memset_align(s, c, n);
}

void	*mlxcolor_memset(void *dest, uint32_t c, size_t n)
{
	unsigned char	*s;
	size_t			k;

	s = dest;
	if (!n)
		return (dest);
	*s = (uint8_t)(c);
	*(s + n - 1) = (uint8_t)(c);
	if (n <= 2)
		return (dest);
	*(s + 1) = (uint8_t)(c);
	*(s + 2) = (uint8_t)(c);
	*(s + n - 2) = (uint8_t)(c);
	*(s + n - 3) = (uint8_t)(c);
	if (n <= 6)
		return (dest);
	*(s + 3) = (uint8_t)(c);
	*(s + n - 4) = (uint8_t)(c);
	if (n <= 8)
		return (dest);
	k = -(uintptr_t)s & 3;
	s += k;
	n -= k;
	mlxcolor_memset_prepare(s, c, n);
	return (dest);
}
