
#include "get_next_line_bonus.h"

void	*my_calloc(int elements, int size)
{
	void	*arr;
	char	*swap;
	int		i;

	i = 0;
	arr = (void *)malloc(elements * size);
	if (!arr)
		return (NULL);
	swap = (char *)arr;
	while (i < elements * size)
	{
		swap[i] = 0;
		i++;
	}
	return (arr);
}

int	search_for_char(char *str, char sign)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == sign)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *src, char *dest)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!src || !dest)
		return (NULL);
	new = my_calloc(ft_strlen(src) + ft_strlen(dest) + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		new[i] = src[i];
		i++;
	}
	while (dest[j] != '\0')
	{
		new[i] = dest[j];
		i++;
		j++;
	}
	free(src);
	new[i] = '\0';
	return (new);
}