#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
ssize_t	read_and_join(int fd, char *buffer, char **stish);
char	*extract_line(char **stish);
size_t	ft_strlen(const char *s);
int		new_line(char *buffer);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif
