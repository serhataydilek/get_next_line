*This project has been created as part of the 42 curriculum by saydilek.*

# Get Next Line

## Description

Get Next Line is a C project that implements a function capable of returning the next line available from a file descriptor.

```c
char *get_next_line(int fd);
```

Each call continues reading from the current position of the file descriptor and returns one line.

When a newline character exists, it is included in the returned string. If the file ends without a final newline, the remaining data is returned as the last line. Once there is no more data to read, or an error occurs, the function returns `NULL`.

The project focuses on understanding file descriptors, the `read()` system call, static storage duration, dynamic memory management, and the difference between data read from a file and data that still has to be returned.

## Implementation

`read()` works with a number of bytes rather than with complete lines. A single call may therefore read less than one line or may read beyond the end of the line that has to be returned.

To handle this, the implementation keeps unread data inside a static pointer named `stash`.

The general flow is:

```text
get_next_line
      |
      v
ft_read_stash
      |
      +--> ft_find_newline
      |
      +--> ft_read_chunk
              |
              +--> read
              |
              +--> ft_strjoin
      |
      v
ft_get_line
      |
      v
ft_get_rest
      |
      v
return line
```

### Reading data

`ft_read_stash()` is responsible for obtaining enough data to produce the next line.

A temporary buffer of `BUFFER_SIZE + 1` bytes is allocated. The extra byte is reserved for the terminating `'\0'`.

While the current stash does not contain a newline and the end of the file has not been reached, `ft_read_chunk()` performs another call to `read()`.

The newly read chunk is terminated with `'\0'` and joined to the current stash using `ft_strjoin()`.

Reading stops as soon as:

- a newline is available in the stash,
- `read()` reaches EOF, or
- an error occurs.

This prevents the function from unnecessarily reading the complete file when the next line is already available.

### Extracting the line

Once enough data has been collected, `ft_get_line()` creates a new allocation containing the first line from the stash.

For example:

```text
stash = "hello world\nremaining data"
```

produces:

```text
line = "hello world\n"
```

The newline is included when it exists.

### Preserving the remainder

After the line has been created, `ft_get_rest()` copies everything following the first newline into a new allocation.

Using the previous example:

```text
old stash = "hello world\nremaining data"
line      = "hello world\n"
new stash = "remaining data"
```

The old stash is then freed.

Because the stash is static, the new value remains available when `get_next_line()` is called again.

If there is no data after the returned line, the stash becomes `NULL`.

## Helper Functions

The implementation uses the following helpers:

- `ft_strlen()`  
  Returns the length of a string. A `NULL` pointer is treated as length zero so the initial empty stash can be handled safely.

- `ft_find_newline()`  
  Searches a string for the first `'\n'`.

- `ft_strjoin()`  
  Allocates a new string containing the current stash followed by the newly read buffer.

- `ft_read_chunk()`  
  Performs one `read()` operation and appends the result to the stash.

- `ft_read_stash()`  
  Repeatedly reads chunks until a complete line is available or reading has finished.

- `ft_get_line()`  
  Allocates and returns the first line stored in the stash.

- `ft_get_rest()`  
  Allocates the unread data found after the returned line so it can be preserved for the next call.

## BUFFER_SIZE

The amount requested from `read()` during each operation is controlled by the `BUFFER_SIZE` macro.

The header provides a default value when one is not supplied during compilation:

```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
```

A different value can be supplied with the compiler:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 ...
```

or:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 ...
```

Changing `BUFFER_SIZE` changes how many read operations may be necessary, but it must not change the final lines returned by the function.

A small value can split a line across many reads, while a large value can place several lines into the stash at once.

## Bonus

The mandatory implementation maintains one static stash:

```c
static char *stash;
```

This is enough when calls are made sequentially on the same file descriptor.

The bonus version allows several file descriptors to be read in an interleaved order.

It uses one static array:

```c
static char *stash[MAX_FD];
```

Each index belongs to one file descriptor:

```text
fd 3 -> stash[3]
fd 4 -> stash[4]
fd 5 -> stash[5]
```

Therefore a sequence such as:

```c
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd1);
get_next_line(fd2);
```

keeps the remaining data of both descriptors separate.

The implementation defines:

```c
#define MAX_FD 1024
```

`1024` is an implementation limit chosen for the static descriptor table; it is not a value required by the subject.

Before using `stash[fd]`, the bonus implementation checks that the descriptor is inside the supported range.

The array itself is still one static variable.

## Project Files

Mandatory:

```text
get_next_line.c
get_next_line.h
get_next_line_utils.c
```

Bonus:

```text
get_next_line_bonus.c
get_next_line_bonus.h
get_next_line_utils_bonus.c
```

Documentation:

```text
README.md
```

## Instructions

The project can be checked for compilation without a test program using:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c \
get_next_line.c get_next_line_utils.c
```

For local testing with a `main.c`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
main.c get_next_line.c get_next_line_utils.c -o gnl_test
```

Then run:

```bash
./gnl_test
```

To test another buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
main.c get_next_line.c get_next_line_utils.c -o gnl_test
```

### Bonus compilation

With a bonus test program:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c \
-o gnl_bonus_test
```

## Important Cases

The implementation should be tested with:

- an empty file,
- one character,
- one line,
- several lines,
- consecutive newline characters,
- a file ending with `'\n'`,
- a file without a final `'\n'`,
- lines shorter than `BUFFER_SIZE`,
- lines larger than `BUFFER_SIZE`,
- `BUFFER_SIZE=1`,
- large `BUFFER_SIZE` values,
- standard input,
- invalid file descriptors,
- several interleaved file descriptors in the bonus version.

## Memory Management

The implementation dynamically allocates the read buffer, the accumulated stash, the returned line, and the remaining stash when necessary.

Ownership is handled so that obsolete allocations are released before their addresses are lost.

During a normal call:

```text
temporary read buffer
        |
        v
joined into stash
        |
        v
buffer freed

old stash
   |
   +--> line allocated
   |
   +--> rest allocated
   |
   v
old stash freed
```

The caller owns the line returned by `get_next_line()` and is responsible for freeing it.

## Resources

Resources used while studying the project:

- `man 2 read`
- `man 3 malloc`
- `man 3 free`
- 42 Get Next Line subject
- Documentation about UNIX file descriptors
- Documentation about static storage duration in C

Useful manual pages:

```bash
man 2 read
man 3 malloc
man 3 free
```

## AI Usage

AI was used as a learning and review tool during the project.

It was used to:

- explain file descriptors and the behavior of `read()`,
- trace the program flow function by function,
- discuss static variables and the lifetime of the stash,
- review memory ownership and cleanup paths,
- compare the mandatory and bonus designs,
- plan edge-case and multi-file-descriptor tests,
- review the implementation against the project subject,
- assist with the structure and wording of this README.

The implementation was reviewed alongside these explanations so that the behavior of each function and the reason for each design choice could be understood.