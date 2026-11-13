*This project has been created as part of the 42 curriculum by abait-br.*

# get_next_line

## Description

`get_next_line` is a C function that returns **one line at a time** from a file descriptor. Each call returns the next line, including its terminating `\n` (if there is one), and returns `NULL` when there is nothing left to read or when an error occurs.

```c
char *get_next_line(int fd);
```

The goal of the project is to learn about:

- **static variables**, which keep state between calls;
- **file descriptors** and the `read()` system call;
- **dynamic memory management**, with no leaks and no invalid reads;
- reading input in chunks of a size that is **unknown at compile time** (`BUFFER_SIZE`).

The function works on regular files as well as on standard input.

### Algorithm

The implementation uses a `static char *scraps` (the "scraps") that holds the data that has been read from the file descriptor but not yet returned to the caller.

1. **Validate** the input: return `NULL` if `fd < 0`, if `BUFFER_SIZE <= 0`, or if `read(fd, NULL, 0)` fails. In the last case the scraps is freed, so nothing leaks.
2. **Fill the scraps** (`read_to_scraps`): read `BUFFER_SIZE` bytes at a time into a temporary buffer and append them to the scraps with `ft_strjoin`. Stop as soon as the scraps contains a `\n` or `read` returns `0` (EOF).
3. **Extract the line** (`extract_line`): allocate a new string, copy everything up to and including the first `\n`, then shift the remaining data to the start of the scraps with `ft_memmove`. If nothing remains, the scraps is freed and set to `NULL`.
4. **EOF without a trailing newline**: the whole scraps is returned as the last line, and the scraps is set to `NULL`.
5. **Errors**: if `read` or any `malloc` fails, everything that was allocated is freed and `NULL` is returned.

**Why this design:** a single static pointer is the simplest structure that satisfies the subject. The scraps makes the function independent of `BUFFER_SIZE`: any extra bytes read past the newline are kept for the next call instead of being lost. Compared to a linked list of buffers, a plain string is easier to reason about and to free correctly.

**Trade-off:** every `read` re-joins the whole scraps with the new buffer, so a very long line combined with a very small `BUFFER_SIZE` (for example `1`) is slow. For normal line lengths and buffer sizes the cost is negligible.

### Bonus: multiple file descriptors

The bonus version can read from several file descriptors at the same time (for example fd 3, then fd 4, then fd 3 again) without losing the reading state of any of them. It still uses a **single static variable**, which stores one scraps per file descriptor instead of a single scraps. The rest of the algorithm is the same as above, applied to the scraps that belongs to the given `fd`.

## Instructions

### Compilation

Compile the project with your own `main` and a `BUFFER_SIZE` of your choice:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

If `-D BUFFER_SIZE=n` is not given, the header defines a default value of `42`.

The bonus part is compiled the same way, with the `_bonus` files:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

### Usage

Include the header and call the function in a loop until it returns `NULL`. Every returned line must be freed by the caller.

```c
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

### Behavior summary

| Situation | Result |
|-----------|--------|
| Next line available | The line, including `\n` if present |
| Last line without `\n` | The line without `\n` |
| EOF reached or empty file | `NULL` |
| Invalid / closed `fd`, `BUFFER_SIZE <= 0` | `NULL` |
| `read` or `malloc` failure | `NULL`, with all memory freed |

The mandatory part handles one file descriptor at a time with a single static scraps. The bonus part handles several file descriptors at once.

## Resources

- `man 2 read`, `man 2 open`, `man 3 malloc`
- [Static variables in C](https://en.wikipedia.org/wiki/Static_variable)
- Valgrind and AddressSanitizer documentation, used to check for leaks and invalid memory access

### Use of AI

AI was used for the following tasks:

AI was used as a learning aid to understand how static variable's work . All the code was written and tested by me.
