#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# define BUFF_SIZE 10000
# define MAX_FD 12000


int get_next_line(int fd, char **line);

#endif
