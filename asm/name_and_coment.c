
#include "asm.h"

void    is_space(char *line, int *i)
{
    while (line[(*i)] && line[(*i)] < 33)
        (*i)++;
}

int     ft_search_name_or_coment(char *lin, char **name, int fd, int *tab)
{
    int     k;

    k = -1;
    while (lin[tab[0]] != '"')
    {
        (*name)[++k] = lin[tab[0]];
        if (k == tab[2])
            return (my_erormanager("", ft_tab(0, 0, 0), 8));
        tab[0]++;
        if (lin[tab[0]] == '\0')
        {
            ft_strdel(&lin);
            get_next_line(fd, &lin);
            tab[1]++;
            tab[0] = 0;
        }
    }
    tab[0]++;
    is_space(lin, &tab[0]);
    return (0);
}

int     ft_valid_name(char *lin, int *i, int fd, t_all **all)
{
    char    *name;
    int     j;
    int     *tab;

    j = 0;
    name = (*all)->header->prog_name;
    is_space(lin, &j);
    j += ft_strlen(NAME_CMD_STRING);
    is_space(lin, &j);
    if (lin[j] != '"')
        return (my_erormanager("", ft_tab(*i, j, 0), 1));
    j++;
    tab = ft_tab(j, *i, PROG_NAME_LENGTH);
    if (ft_search_name_or_coment(lin, &name, fd, tab) == -1)
    {
        free(tab);
        return (-1);
    }
    *i = tab[1];
    j = tab[0];
    free(tab);
    if (lin[j] != '\0' && lin[j] != '#' && lin[j] != ';')
        return (my_erormanager(lin + j, ft_tab(*i, j, 1), 2));
    return (0);
}

int     ft_valid_coment(char *lin, int *i, int fd, t_all **all)
{
    char    *name;
    int     j;
    int     *tab;

    j = 0;
    name = (*all)->header->comment;
    is_space(lin, &j);
    j += ft_strlen(COMMENT_CMD_STRING);
    is_space(lin, &j);
    if (lin[j] != '"')
        return (my_erormanager("", ft_tab(*i, j, 0), 1));
    j++;
    tab = ft_tab(j, *i, COMMENT_LENGTH);
    if (ft_search_name_or_coment(lin, &name, fd, tab) == -1)
    {
        free(tab);
        return (-1);
    }
    *i = tab[1];
    j = tab[0];
    free(tab);
    if (lin[j] != '\0' && lin[j] != '#' && lin[j] != ';')
        return (my_erormanager(lin + j, ft_tab(*i, j, 1), 2));
    return (0);
}


int     name_and_coment(int fd, int *i, t_all **all)
{
    char    *line;
    int     stop;
    int     j;

    stop = 0;
    while (get_next_line(fd, &line) > 0)
    {
        j = 0;
        (*i)++;
        is_space(line, &j);
        if (ft_coment(line))
        {
            ft_strdel(&line);
            continue ;
        }
        else if (!ft_strncmp(line + j, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
        {
            if (ft_valid_name(line, i, fd, all) == -1)
            {
                ft_strdel(&line);
                return (-1);
            }
            stop++;
        }
        else if (!ft_strncmp(line + j, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
        {
            if (ft_valid_coment(line, i, fd, all) == -1)
            {
                ft_strdel(&line);
                return (-1);
            }
            stop++;
        }
        else
            return (my_erormanager(line, ft_tab(*i, j, 0), 9));
        if (stop == 2)
            break ;
    }
    return (1);
}