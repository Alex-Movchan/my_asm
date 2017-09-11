//
// Created by alex on 16.07.17.
//

#ifndef ASM_ASM_H
#define ASM_ASM_H

#include <fcntl.h>
#include "libft/libft.h"
#include "op.h"
#define BYTE 8

typedef	struct		s_stak
{
	char            *funk_name;
	unsigned int    caret_size;
	struct s_stak   *next;
}			    	t_stak;

typedef struct      s_lin
{
    char            *lin;
    int             i;
    t_stak          *stak;
}                   t_lin;

typedef struct		s_prog
{
	int 			i;
	char			*label1;
    char            *label2;
	char			*label3;
    int             i_j[2];
    int	value[MAX_ARGS_NUMBER];
	unsigned int	caret;
	int				coding_byte;
	int				arg[MAX_ARGS_NUMBER];
	struct s_prog	*next;
}					t_prog;

typedef struct		s_all
{
	t_prog			*prog;
	t_stak			*stak;
    t_header        *header;
}					t_all;

int       ft_compiler(char *str, char *name);
int       my_erormanager(char *str, int *tab, int error);
int       *ft_tab(int i, int j, int k);
int     translation_into_bytcode(int fd, int *i, char *line, t_all **all);
int     ft_serch_label(char *line, int *i, int *j, t_all **all);
char    *ft_strnduplen(char *str, int *start, int finish);
int     ft_instruction(char *line, int *i, int *j, t_all **all);
int     ft_argument(char *line, int *i, int *j, t_all **all);
int     valid_direkt(char *str, int *i, int *j, t_prog **prog);
int     valid_registr(char *str, int *tab, int *j, t_prog **prog);
int     valid_indir(char *str, int *tab, int *j, t_prog **prog);
int      ft_coding_byt(t_prog *prog);
unsigned int    ft_size_program(t_all **all, t_prog *prog);
int     ft_search_availability_label(t_all **all);
void    ft_write_program(t_all *all, char *str);
int     ft_coment(char *line);
int     name_and_coment(int fd, int *i, t_all **all);
char    *serch_coment(char *lin);
void    ft_dell_all(t_all **all);
int     ft_islabel(char *str, int *i, int *j, t_prog **prog);


#endif //ASM_ASM_ds
