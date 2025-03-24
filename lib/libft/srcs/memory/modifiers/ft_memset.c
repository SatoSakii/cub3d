/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:54:54 by albernar          #+#    #+#             */
/*   Updated: 2025/03/10 19:22:32 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

void	memset_align(void *s, int c, size_t n)
{
	uint32_t	c32;
	uint64_t	c64;
	size_t		k;

	c32 = ((uint32_t)-1) / 255 * (unsigned char)c;
	c64 = c32 | ((uint64_t)c32 << 32);
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

void	memset_prepare(void *s, int c, size_t n)
{
	uint32_t	c32;

	n &= -4;
	c32 = ((uint32_t)-1) / 255 * (unsigned char)c;
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
	memset_align(s, c, n);
}

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*s;
	size_t			k;

	s = dest;
	if (!n)
		return (dest);
	*s = c;
	*(s + n - 1) = c;
	if (n <= 2)
		return (dest);
	*(s + 1) = c;
	*(s + 2) = c;
	*(s + n - 2) = c;
	*(s + n - 3) = c;
	if (n <= 6)
		return (dest);
	*(s + 3) = c;
	*(s + n - 4) = c;
	if (n <= 8)
		return (dest);
	k = -(uintptr_t)s & 3;
	s += k;
	n -= k;
	memset_prepare(s, c, n);
	return (dest);
}
