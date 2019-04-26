#include "get_next_line.h"
#define MAX_FD 12000

int		ft_get_next_line(char **stack, char **line)
{
    int		i;
    char	*str;
     
    i = -1;
    str = *stack;
    while (str[++i])
        if (str[i] == '\n')
        {
            if ((*line = ft_strsub(str, 0, i)) && (*stack = ft_strdup(str + i + 1)))
                return (1);
            else
                return (-1);
        }
    *line = ft_strdup(str);
    ft_strdel (stack);
    if (*line)
        return (1);
    return (-1);
}

int		ft_free_and_return(int ret_v, char **wtf)
{
    free(*wtf);
    return (ret_v);
}

int		get_next_line(int fd, char **line)
{
    int				br;
    char			*ret;
    static	char	*str[MAX_FD];
    
    if (!(ret = (char *)malloc(sizeof(*ret) * BUFF_SIZE)) || !line || fd < 0 || fd > MAX_FD ||  ((br = read(fd, ret, BUFF_SIZE)) < 0))
        return (ft_free_and_return(-1, &ret));
    if ((!str[fd] && !br) || (str[fd] && !*str[fd] && !br))
        return (ft_free_and_return(0, &ret));
    if (!br)
        return (ft_free_and_return(ft_get_next_line(&str[fd], line), &ret));
    else
    {
        if (!(str[fd] ? (str[fd] = ft_strjoin(str[fd], ft_strsub(ret, 0, br))) : (str[fd] = ft_strsub(ret, 0, br))))
            return (ft_free_and_return(-1, &ret));
        while (!ft_strchr(str[fd], '\n'))
            return (ft_free_and_return(get_next_line(fd, line), &ret));
        return (ft_free_and_return(ft_get_next_line(&str[fd], line), &ret));
    }
}
