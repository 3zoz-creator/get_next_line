#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char const *s1, char const *s2)
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

static int	new_line(char *buffer)
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

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stish;
	char		*tmp;
	char		*line;
	int			got_it;
	int			count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (new_line(stish) == -1)
	{
		tmp = stish;
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			free(stish);
			stish = NULL;
			return (NULL);
		}
		if (count == 0)
		{
			free(buffer);
			break ;
		}
		buffer[count] = '\0';
		stish = ft_strjoin(stish, buffer);
		free(tmp);
		if (stish == NULL)
		{
			free(buffer);
			break ;
		}
	}
	got_it = new_line(stish);
	line = malloc(got_it + 2);
	if (!line)
		return (NULL);
	ft_memcpy(line, stish, got_it + 1);
	line[got_it + 1] = '\0';
	ft_memmove(stish, stish + got_it + 1, ft_strlen(stish + got_it + 1) + 1);
	if (count != 0)
		free(buffer);
	return (line);
}
