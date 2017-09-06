
#include "asm.h"

static t_prog  *last_elem(t_prog *prog)
{
    t_prog *lst;

    lst = prog;
    while (lst->next)
        lst = lst->next;
    return (lst);
}

static int     valid_argument(char *str, int *i, int *j, t_prog **prog)
{
    while (*str && *str < 33 && (*j)++)
        str++;
    if (str[0] == DIRECT_CHAR)
        return (valid_direkt(str, i, j, prog));
    else if (str[0] == 'r')
        return (valid_registr(str, i, j, prog));
    else
        return (valid_indir(str, i, j, prog));
}

static int     serch_argument(char **agr, int *i, int *j, t_all **all)
{
    t_prog  *prog;
    int     k;

    k = -1;
    prog = last_elem((*all)->prog);
    prog->caret = (*all)->header->prog_size;
    while (agr[++k]) {
        if (valid_argument(agr[k], ft_tab(*i, k, 0), j, &prog) == -1)
            return (-1);
        if ((g_tab[prog->i].arg[k] & prog->arg[k]) != prog->arg[k])
            return (my_erormanager(ft_strdup(g_tab[prog->i].name), ft_tab(0, 0, k), 4));
        if (k > g_tab[prog->i].count_arg)
            return (my_erormanager(g_tab[prog->i].name, ft_tab(0, 0, k), 4));
        (*j) += ft_strlen(agr[k]) - 1;
    }
    if (g_tab[prog->i].coding_byte == 1)
            prog->coding_byte = ft_coding_byt(prog);
    if (k != g_tab[prog->i].count_arg)
        return (my_erormanager(g_tab[prog->i].name, ft_tab(0, 0, 0), 3));
    (*all)->header->prog_size += ft_size_program(all, prog);
    return (0);
}

int     ft_argument(char *line, int *i, int *j, t_all **all)
{
    char    *src;
    char    **argument;
    int     k;
    t_prog  *prog;

    k = 0;
    src = line;
    while (++k < (*j))
        src++;
    if (!(argument = ft_strsplit(src, SEPARATOR_CHAR)) || !*argument)
        return (my_erormanager("\0", ft_tab(*i, *j, 0), 2));

    if (serch_argument(argument, i, j, all) == -1)
        return (-1);
 //підрахунок розміру строки в хедер +=
    return (0);
}