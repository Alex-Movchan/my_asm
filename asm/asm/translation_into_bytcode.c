/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_into_bytcode.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:11:56 by amovchan          #+#    #+#             */
/*   Updated: 2017/09/14 20:12:02 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_coment(char *line)
{
	int		i;

	i = -1;
	while (line[++i] && line[i] < 33)
		;
	if (line[i] == COMMENT_CHAR || line[i] == ';' || line[i] == '\0')
	{
		ft_strdel(&line);
		return (1);
	}
	return (0);
}

static int	last_byt(int fd)
{
	char	src[1];

	if (lseek(fd, -1, 1) < 0)
	{
		ft_printf("{fd}Error lseek\n", 2);
		return (-1);
	}
	if (read(fd, src, 1) < 0)
	{
		ft_printf("{fd}Error read\n", 2);
		return (-1);
	}
	if (src[0] != '\n')
		return (my_erormanager("", ft_tab(0, 0, 0), 10));
	return (0);
}

static int	ft_cmp_namne_comment(char **src)
{
	char	*str;

	str = *src;
	while (*str && *str < 33)
		str++;
	if (!ft_strncmp(str, NAME_CMD_STRING, 5) ||
			!ft_strncmp(str, COMMENT_CMD_STRING, 8))
	{
		ft_strdel(src);
		return (0);
	}
	return (1);
}

int			translation_into_bytcode(int fd, int *i, char *line, t_all **all)
{
	int		j;

	while (get_next_line(fd, &line) > 0)
	{
		(*i)++;
		j = 0;
		if (!ft_cmp_namne_comment(&line))
			break ;
		line = serch_coment(line);
		if (ft_coment(line))
			continue ;
		if (ft_serch_label(line, i, &j, all) == -1 ||
				ft_instruction(line, i, &j, all) == -1)
		{
			ft_strdel(&line);
			return (-1);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (last_byt(fd) == -1 || ft_search_availability_label(all) == -1)
		return (-1);
	return (1);
}
