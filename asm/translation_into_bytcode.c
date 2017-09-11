
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

int     last_byt(int fd)
{
    char    src[1];

    if (lseek(fd, -1, 1) < 0)
    {
        ft_printf("{fd}Error lseek\n", 2);
        return (-1);
    }
    if (read(fd, src, 1) < 0)
    {
        ft_printf("{fd}Error read\n", 2);
        return (-1);
    }
    if (src[0] != '\n')
        return (my_erormanager("", ft_tab(0, 0, 0), 10));
    return (0);
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

int     ft_cmp_namne_comment(char **src)
{
    char *str;

    str = *src;
    while (*str && *str < 33)
        str++;
    if (!ft_strncmp(str, NAME_CMD_STRING, 5) || !ft_strncmp(str, COMMENT_CMD_STRING, 8))
    {
        ft_strdel(src);
        return (0);
    }
    return (1);
}

int     translation_into_bytcode(int fd, int *i, char *line, t_all **all)
{
    int     j;
    char    *src;

    src = NULL;
    while (get_next_line(fd, &line) > 0) {
        (*i)++;
        j = 0;
        if (!ft_cmp_namne_comment(&line))
            break;
        line = serch_coment(line);
        if (ft_coment(line) || !ft_strcmp_not_space(line, src)) {
            ft_strdel(&line);
            continue;
        }
        if (ft_serch_label(line, i, &j, all) == -1) {
            ft_strdel(&line);
            return (-1);
        }
        if ((ft_instruction(line, i, &j, all)) == -1)
        {
            ft_strdel(&line);
            return (-1);
        }
        ft_strdel(&src);
        src = ft_strdup(line);
        ft_strdel(&line);
    }
    ft_strdel(&line);
    ft_strdel(&src);
    if (last_byt(fd) == -1)
        return (-1);
    if (ft_search_availability_label(all) == -1)
        return (-1);
    return (1);
}