
#include "asm.h"

unsigned int    rewers(int nb)
{
    unsigned int res;

    res = 0;
    res = res | ((nb & 0xFF) << (3 * BYTE));
    res = res | ((nb & 0xFF00) << BYTE);
    res = res | ((nb & 0xFF0000) >> BYTE);
    res = res | ((nb & 0xFF000000) >> (3 * BYTE));
    return (res);
}

unsigned short  swap_bit(unsigned short nb)
{
    return (nb >> BYTE | nb << BYTE);
}

void    write_argument(int fd, t_prog *prog)
{
    int     i;
    int nb;

    i = -1;
    while (++i < g_tab[prog->i].count_arg)
    {
        if (prog->arg[i] == T_REG)
            write(fd, &prog->value[i], 1);
        else if ((prog->arg[i] == T_DIR && g_tab[prog->i].flag_direct_size == 1) || prog->arg[i] == T_IND)
        {
            nb = swap_bit((unsigned short)prog->value[i]);
            write(fd, &nb, 2);
        }
        else if (prog->arg[i] == T_DIR )
        {
            nb = rewers(prog->value[i]);
            write(fd, &nb, 4);
        }
    }
}

void    ft_write_prigram_byt(t_all *all, int fd)
{
    t_prog  *prog;

    prog = all->prog;
    while (prog)
    {
        write(fd, &g_tab[prog->i].op_code, 1);
        if (g_tab[prog->i].coding_byte == 1)
            write(fd, &prog->coding_byte, 1);
        write_argument(fd, prog);
        prog= prog->next;
    }
}

void    ft_write_program(t_all *all, char *file_path)
{
    int fd;
    int megic;

    fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    megic = rewers(all->header->magic);
    write(fd, &megic, sizeof(unsigned int));
    write(fd, all->header->prog_name, PROG_NAME_LENGTH + 4);
    all->header->prog_size = rewers(all->header->prog_size);
    write(fd, &all->header->prog_size, 4);
    write(fd, all->header->comment, COMMENT_LENGTH + 4);
    ft_write_prigram_byt(all, fd);
    close(fd);
}
