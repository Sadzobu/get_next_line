#include "get_next_line.h"

int		ft_get_next_line_stack(char **line, char **stack)
{
    int i;
    char *str;
     
    i = -1;
    str = *stack;
    while (str[++i])
        if (str[i] == '\n')
        {
            *line = ft_strsub(str, 0, i);
            *stack = ft_strdup(str + i + 1);
            if (*line && *stack)
                return (1);
            return (-1);
        }
    return (0);
}

int		ft_get_next_line(int fd, char **line, char **heap)
{
    static char *str[12000];
    char *ret;
    int br;

    ret = *heap;
    while ((br = read(fd, ret, BUFF_SIZE)) > 0)
    {
        str[fd] ? (str[fd] = ft_strjoin(str[fd], ft_strsub(ret, 0, br))) : (str[fd] = ft_strsub(ret, 0, br));
        if (!str[fd])
            return (-1);
        if ((br = ft_get_next_line_stack(line, &str[fd])))
            return (br);
    }
    if (br < 0)
        return (-1);
    if (str[fd] && (br = ft_get_next_line_stack(line, &str[fd])))
        return (br);
    if (str[fd] && *str[fd])
    {
        *line = ft_strdup(str[fd]);
        str[fd] = NULL;
        if (*line)
            return (1);
        return (-1);
    }
    return (0);
}

int		get_next_line(int fd, char **line)
{
    char		*ret;
    int			res;

    if (!line || fd < 0 || fd >= 12000 || !(ret = (char *)malloc(sizeof(*ret) * BUFF_SIZE)))
        return (-1);
    res = ft_get_next_line(fd, line, &ret);
    free(ret);
    return (res);
}
