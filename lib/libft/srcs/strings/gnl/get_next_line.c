/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:44:42 by swenn             #+#    #+#             */
/*   Updated: 2025/02/10 10:51:28 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

static char	*ft_loop(int fd, int bytes_read, char *backslash, char *str)
{
	static char	buffer[BUFFER_SIZE] = {0};

	bytes_read = 1;
	str = NULL;
	while (1)
	{
		if (!*buffer)
			bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		backslash = ft_strchr(buffer, '\n');
		if (!backslash)
		{
			str = ft_strnjoin(str, buffer, BUFFER_SIZE, 1);
			ft_memset(buffer, 0, BUFFER_SIZE);
			continue ;
		}
		str = ft_strnjoin(str, buffer, backslash - buffer + 1, 1);
		ft_memmove(buffer, backslash + 1, BUFFER_SIZE);
		break ;
	}
	if (bytes_read == -1)
		ft_memset(buffer, 0, BUFFER_SIZE);
	return (str);
}

char	*get_next_line(int fd)
{
	char	*str;
	int		bytes_read;
	char	*backslash;

	bytes_read = 0;
	backslash = NULL;
	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_loop(fd, bytes_read, backslash, str);
	return (str);
}
