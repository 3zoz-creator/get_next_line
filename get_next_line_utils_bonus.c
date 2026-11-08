/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-br <abait-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 21:38:43 by abait-br          #+#    #+#             */
/*   Updated: 2026/11/07 17:13:00 by abait-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	read_and_join(int fd, char *buffer, char **stish)
{
	ssize_t	count;
	char	*tmp;

	count = read(fd, buffer, BUFFER_SIZE);
	if (count <= 0)
		return (count);
	buffer[count] = '\0';
	tmp = *stish;
	*stish = ft_strjoin(*stish, buffer);
	free(tmp);
	if (!*stish)
		return (-1);
	return (count);
}

char *extract_line(char **stish)
{
	char	*line;
	int		got_it;

	got_it = new_line(*stish);
	line = malloc(got_it + 2);
	if (!line)
	{
		free(*stish);
		*stish = NULL;
		return (NULL);
	}
	ft_memcpy(line, *stish, got_it + 1);
	line[got_it + 1] = '\0';
	ft_memmove(*stish, (*stish) + got_it + 1,
		ft_strlen((*stish) + got_it + 1) + 1);
	if (!**stish)
	{
		free(*stish);
		*stish = NULL;
	}
	return (line);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*dst;
	size_t			i;

	s = (unsigned char *)src;
	dst = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		dst[i] = s[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*s;
	size_t				i;

	dst = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (n == 0 || dest == src)
		return (dest);
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			i--;
			dst[i] = s[i];
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dst);
}
