/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-br <abait-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 20:53:34 by abait-br          #+#    #+#             */
/*   Updated: 2026/11/12 20:59:54 by abait-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

ssize_t	read_and_join(int fd, char *buffer, char **scraps)
{
	ssize_t	count;
	char	*tmp;

	count = read(fd, buffer, BUFFER_SIZE);
	if (count <= 0)
		return (count);
	buffer[count] = '\0';
	tmp = *scraps;
	*scraps = ft_strjoin(*scraps, buffer);
	free(tmp);
	if (!*scraps)
		return (-1);
	return (count);
}

char	*read_to_scraps(int fd, char **scraps)
{
	char	*buffer;
	ssize_t	count;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(*scraps);
		return (NULL);
	}
	count = 1;
	while (new_line(*scraps) == -1 && count > 0)
		count = read_and_join(fd, buffer, scraps);
	free(buffer);
	if (count < 0)
	{
		free(*scraps);
		return (NULL);
	}
	return (*scraps);
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
