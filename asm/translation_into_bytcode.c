
#include "asm.h"

int     ft_coment(char *line)
{
    int     i;

    i = -1;
    while (line[++i] && line[i] < 33)
        ;
    if (line[i] == COMMENT_CHAR || line[i] == ';' || line[i] == '\0')
        return (1);
    return (0);
}

char    *serch_coment(char *lin)
{
    int     i;
    char    *src;

    i = -1;
    while (lin[++i] && lin[i] != COMMENT_CHAR && lin[i] != ';')
        ;
    if (lin[i] == '\0')
        return (lin);
    src = ft_strndup(lin, (size_t)i);
    src[i] = '\0';
    ft_strdel(&lin);
    return (src);
}

int     ft_strcmp_not_space(char *str, char *src)
{
    int     i;
    int     j;

    i = -1;
    j = -1;
    if (!src)
        return (1);
    while (*src && *src < 33)
        src++;
    while (*str && *str < 33)
        str++;
    while (src[++i] && str[++j])
    {
        while (src[i] && src[i] < 33)
            i++;
        while (str[j] && str[j] < 33)
            j++;
        if (src[i] != str[j])
            break ;
    }
    return (src[i] - str[j]);
}

int     translation_into_bytcode(int fd, int *i, char *line, t_all **all)
{
    int     j;
    char    *src;

    src = NULL;
    while (get_next_line(fd, &line) > 0)
    {
        (*i)++;
        j = 0;
       // if ()
        line = serch_coment(line);
        if (ft_coment(line) || !ft_strcmp_not_space(line, src))
        {
            ft_strdel(&line);
            continue;
        }
        if (ft_serch_label(line, i, &j, all) == -1)
            return (-1);
        if ((ft_instruction(line, i, &j, all)) == -1)
            return (-1);
        ft_strdel(&src);
        src = ft_strdup(line);
        ft_strdel(&line);
    }
//    if (!line || line[0] != '\0')
//    {
//        ft_strdel(&line);
//        return (my_erormanager("", ft_tab(0, 0, 0), 10));
//    }10
    if (ft_search_availability_label(all) == -1)
        return (-1);
    return (1);
}