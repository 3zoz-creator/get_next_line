/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-br <abait-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 20:53:38 by abait-br          #+#    #+#             */
/*   Updated: 2026/11/13 17:42:21 by abait-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s2)
		return (NULL);
	len2 = ft_strlen(s2);
	if (!s1)
	{
		str = malloc(len2 + 1);
		if (!str)
			return (NULL);
		ft_memcpy(str, s2, len2);
		str[len2] = '\0';
		return (str);
	}
	len1 = ft_strlen(s1);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

ssize_t	new_line(char *scraps)
{
	ssize_t	got_it;

	if (!scraps)
		return (-1);
	got_it = 0;
	while (scraps[got_it])
	{
		if (scraps[got_it] == '\n')
			return (got_it);
		got_it++;
	}
	return (-1);
}

char	*extract_line(char **scraps)
{
	char	*line;
	ssize_t	got_it;

	got_it = new_line(*scraps) + 1;
	line = malloc(got_it + 1);
	if (!line)
	{
		free(*scraps);
		*scraps = NULL;
		return (NULL);
	}
	ft_memcpy(line, *scraps, got_it);
	line[got_it] = '\0';
	ft_memmove(*scraps, *scraps + got_it, ft_strlen(*scraps + got_it) + 1);
	if (!**scraps)
	{
		free(*scraps);
		*scraps = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*scraps[FD_LIMIT];
	char		*line;

	if (fd < 0 || fd > FD_LIMIT|| BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, NULL, 0) == -1)
	{
		free(scraps[fd]);
		scraps[fd] = NULL;
		return (NULL);
	}
	scraps[fd] = read_to_scraps(fd, &scraps[fd]);
	if (!scraps[fd] || !(*scraps[fd]))
	{
		free(scraps[fd]);
		scraps[fd] = NULL;
		return (NULL);
	}
	if (new_line(scraps[fd]) == -1)
	{
		line = scraps[fd];
		scraps[fd] = NULL;
		return (line);
	}
	return (extract_line(&scraps[fd]));
}
