
#include "asm.h"

int     search_label_in_stak(t_stak *stak, char *name, t_prog **prog, int i)
{
    while (stak)
    {
        if (!ft_strcmp(stak->funk_name, name))
        {
            (*prog)->value[i] = (int)stak->caret_size - (int)(*prog)->caret;
            return (1);
        }
        stak = stak->next;
    }
    return (my_erormanager(name, ft_tab((*prog)->i_j[0], (*prog)->i_j[1], 0), 6));
}

int     ft_search_availability_label(t_all **all)
{
    t_prog  *prog;
    t_stak  *stak;

    prog = (*all)->prog;
    stak = (*all)->stak;
    while (prog)
    {
        if (prog->label1)
            if (search_label_in_stak(stak, prog->label1, &prog, 0) == -1)
                return (-1);
        if (prog->label2)
            if (search_label_in_stak(stak, prog->label2, &prog, 1) == -1)
                return (-1);
        if (prog->label3)
            if (search_label_in_stak(stak, prog->label3, &prog, 2) == -1)
                return (-1);
        prog = prog->next;
    }
    return (1);
}
