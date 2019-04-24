#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
    char *ret;
    static char *str[12000];
    int br;
    int i;

    if (!line || fd < 0 || fd >= 12000 || !(ret = (char *)malloc(sizeof(*ret) * BUFF_SIZE)))
        return (-1);
    while ((br = read(fd, ret, BUFF_SIZE)) > 0)
    {
        if (!str[fd])
            str[fd] = ft_strsub(ret, 0, br);
        else
            str[fd] = ft_strjoin(str[fd], ft_strsub(ret, 0, br));
        i = -1;
        while (str[fd][++i])
            if (str[fd][i] == '\n')
            {
                *line = ft_strsub(str[fd], 0, i);
                str[fd] = ft_strdup(str[fd] + i + 1);
                return (1);
            }
    }
    if (br < 0)
        return (-1);
    i = 0;
    if (str[fd])
    {
        while (str[fd][i])
        {
            if (str[fd][i] == '\n')
            {
                *line = ft_strsub(str[fd], 0, i);
                str[fd] = ft_strdup(str[fd] + i + 1);
                return (1);
            }
            i++;
        }
        if (*str[fd])
        {
            *line = ft_strdup(str[fd]);
            str[fd] = NULL;
            return (1);
        }
    }
    return (0);
}
