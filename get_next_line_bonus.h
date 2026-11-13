/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-br <abait-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 20:54:06 by abait-br          #+#    #+#             */
/*   Updated: 2026/11/13 15:10:08 by abait-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
ssize_t	read_and_join(int fd, char *buffer, char **scraps);
char	*read_to_scraps(int fd, char **scraps);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
ssize_t	new_line(char *scraps);
char	*extract_line(char **scraps);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

# ifndef FD_LIMIT
#  define FD_LIMIT 1024
# endif

#endif