
#include "asm.h"

static char *ft_name_file(char *str)
{
    char    *src;
    size_t  size;
    int     i;
    char    *leaks;

    size = ft_strlen(str);
    src = ft_strnew(size - 1);
    i = -1;
    while (++i < size - 1)
        src[i] = str[i];
    src[++i] = '\0';
    leaks = src;
    src = ft_strjoin(src, "cor");
    ft_strdel(&leaks);
    return (src);
}

int main(int argc, char **argv)
{
    int     i;
    char    *name;
    i = 0;

    while (++i < argc)
    {
        name = ft_name_file(argv[i]);
        if (ft_compiler(argv[i], name))
           ft_printf("Writing output program to %s\n", name);
        ft_strdel(&name);
    }
    while (1);
    return (0);
}