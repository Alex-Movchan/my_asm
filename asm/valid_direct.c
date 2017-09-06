
#include "asm.h"

static int     ft_islabel(char *str, int *i, int *j, t_prog **prog)
{
    char    *name;
    int     k;
    int     z;

    k = 2;
    z = -1;
    if (str[2] < 33)
        return (my_erormanager("", ft_tab(i[0], (*j) + 2, 0), 1));
    (*prog)->i_j[0] = *i;
    (*prog)->i_j[1] = *j;
    while (str[k] && str[k] > 33)
        k++;
    name = (char*)malloc(sizeof(char) * k - 1);
    k = 1;
    while (str[++k] && str[k] > 33)
        name[++z] = str[k];
    name[++z] = '\0';
    if (i[1] == 0)
        (*prog)->label1 = name;
    else if (i[1] == 1)
        (*prog)->label2 = name;
    else
        (*prog)->label3 = name;
    return (0);
}

int     valid_direkt(char *str, int *i, int *j, t_prog **prog)
{
    int     k;

    k = 1;
    (*prog)->arg[i[1]] = T_DIR;
    if (str[0] == DIRECT_CHAR && str[1] < 33)
        return (my_erormanager((str + k), ft_tab(i[0], (*j) + 1, 0), 1));
    if (str[1] == LABEL_CHAR)
        return (ft_islabel(str, i, j, prog));
    if (str[k] == '-')
        k++;
    while (str[k] && ft_isdigit(str[k]))
        k++;
    while (str [k] && str[k] < 33)
        k++;
    if (str[k] != '\0')
        return (my_erormanager((str + k), ft_tab(i[0], (*j) + k, 4), 2));
    (*prog)->value[i[1]] = ft_atoi(str + 1);
    return (0);
}