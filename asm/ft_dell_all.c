
#include "asm.h"

void    dell_stack(t_stak **stak)
{
    t_stak  *liaks;

    while (*stak)
    {
        liaks = (*stak);
        (*stak) = (*stak)->next;
        liaks->next = NULL;
        ft_strdel(&(liaks->funk_name));
        free(liaks);
    }
}

void    dell_program(t_prog **prog)
{
    t_prog *liaks;

    while (*prog)
    {
        liaks = *prog;
        *prog = (*prog)->next;
        liaks->next = NULL;
        if (liaks->label1)
            ft_strdel(&(liaks->label1));
        if (liaks->label2)
            ft_strdel(&(liaks->label2));
        if (liaks->label3)
            ft_strdel(&(liaks->label3));
        free(liaks);
    }
}

void    ft_dell_all(t_all **all)
{
    free((*all)->header);
    (*all)->header = NULL;
    dell_stack(&(*all)->stak);
    dell_program(&(*all)->prog);
    free(*all);
}