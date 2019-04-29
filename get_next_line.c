#include "get_next_line.h"

int		ft_free_and_return(int ret_v, char **wtf)
{
    ft_strdel(wtf);
    return (ret_v);
}

int		ft_get_next_line(char **stack, char **line)
{
    int		i;
    char	*str;
    char	*tmp;
     
    i = -1;
    str = *stack;
    while (str[++i])
        if (str[i] == '\n')
        {
            tmp = ft_strdup(*stack);
            ft_strdel(stack);
            if ((*line = ft_strsub(tmp, 0, i)) && (*stack = ft_strdup(tmp + i + 1)))
                return (ft_free_and_return(1, &tmp));
            else
                return (ft_free_and_return(1, &tmp));
        }
    *line = ft_strdup(str);
    ft_strdel(stack);
    if (*line)
        return (1);
    return (-1);
}

void	ft_alloc_str(char **ret, int br, char **str)
{
    char *tmp1;
    char *tmp2;
    
    tmp2 = ft_strsub(*ret, 0, br);
    if (*str)
    {
        tmp1 = ft_strdup(*str);
        ft_strdel(str);
        *str = ft_strjoin(tmp1, tmp2);
        ft_strdel(&tmp1);
    }
    else
        *str = ft_strdup(tmp2);
    ft_strdel(&tmp2);
}

int		get_next_line(int fd, char **line)
{
    int				br;
    char			*ret;
    static	char	*str[MAX_FD];
    
    if (!(ret = (char *)malloc(sizeof(*ret) * BUFF_SIZE)) || !line || fd < 0 || fd > MAX_FD ||  ((br = read(fd, ret, BUFF_SIZE)) < 0))
        return (ft_free_and_return(-1, &ret));
    if ((!str[fd] && !br) || (str[fd] && !*str[fd] && !br))
    {
        ft_strdel(&str[fd]);
        return (ft_free_and_return(0, &ret));
    }
    if (!br)
        return (ft_free_and_return(ft_get_next_line(&str[fd], line), &ret));
    else
    {
        ft_alloc_str(&ret, br, &str[fd]);
        if (!str[fd])
            return (ft_free_and_return(-1, &ret));
        while (!ft_strchr(str[fd], '\n'))
            return (ft_free_and_return(get_next_line(fd, line), &ret));
        return (ft_free_and_return(ft_get_next_line(&str[fd], line), &ret));
    }
}
