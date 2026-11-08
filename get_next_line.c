#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

int	new_line(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*read_to_stash(int fd, char *stish)
{
	char	*buffer;
	ssize_t	count;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(stish);
		return (NULL);
	}
	count = 1;
	while (new_line(stish) == -1 && count > 0)
		count = read_and_join(fd, buffer, &stish);
	free(buffer);
	if (count < 0)
	{
		free(stish);
		return (NULL);
	}
	return (stish);
}

char	*get_next_line(int fd)
{
	static char	*stish;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, NULL, 0) == -1)
	{
    	free(stish);
    	stish = NULL;
    	return (NULL);
	}
	stish = read_to_stash(fd, stish);
	if (!stish || !(*stish))
	{
    	free(stish);
    	stish = NULL;
    	return (NULL);
	}
	if (new_line(stish) == -1)
	{
		line = stish;
		stish = NULL;
		return (line);
	}
	return (extract_line(&stish));
}
