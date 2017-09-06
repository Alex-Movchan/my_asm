
#include "libft.h"

char    *ft_strndup(char *str, size_t len)
{
    char	*src;

    if (!(src = ft_strnew(len)))
        return (NULL);
    if (!(src = ft_strncpy(src, str, len)))
        return (NULL);
    return (src);
}