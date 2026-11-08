#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int     fd;
    int     i;
    char    *line;

    if (argc != 2)
        return (1);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (1);
    i = 0;
    while (i < 6)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        printf("%s", line);
        free(line);
        i++;
    }
    close(fd);
    return (0);
}