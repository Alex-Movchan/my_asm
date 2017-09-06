
#include "asm.h"

static int      serch_code_arg(int nb)
{
    if (nb == T_DIR)
        return (DIR_CODE);
    else if (nb == T_REG)
        return (REG_CODE);
    else
        return (IND_CODE);
}

int      ft_coding_byt(t_prog *prog)
{
    int     coding_byt;
    int     i;
    int     offset_bit;

    i = -1;
    offset_bit = 6;
    coding_byt = 0;
    while (++i < g_tab[prog->i].count_arg)
    {
        coding_byt += serch_code_arg(prog->arg[i]) << offset_bit;
        offset_bit -= 2;
    }
//    ft_printf("%x\n", coding_byt);
    return (coding_byt);
}