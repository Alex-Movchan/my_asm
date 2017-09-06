
#include "asm.h"

int     valid_indir(char *str, int *tab, int *j, t_prog **prog)
{
    int i;

    i = 0;
    (*prog)->arg[tab[1]] = T_IND;
    while (str[i] && str[i] < 33)
        i++;
    if (str[i] == '-')
        i++;
    while (str[i] && ft_isdigit(str[i]))
        i++;
    while (str[i] && str[i] < 33)
        i++;
    if (str[i] != '\0')
        return (my_erormanager(str + i, ft_tab(tab[0], *j, 3), 2));
    (*prog)->value[tab[1]] = (unsigned int)ft_atoi(str);
    return (T_IND);
}