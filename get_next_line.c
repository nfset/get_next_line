/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:46:58 by apieniak          #+#    #+#             */
/*   Updated: 2025/01/19 18:22:23 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 4
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

size_t	ft_strlen(char *str)
{
	int 	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strjoin(char *src, char *dest)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!src || !dest)
		return (NULL);
	new = malloc(ft_strlen(src) + ft_strlen(dest) + 1);
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

char *next_line(char *buff);

char *get_line(char *buff)
{
	char	*line;

	return (line);
}

char	*textF_read(char *buffer, int fd)
{
	char	*buff_supp;
	int	buff_count;

	buff_count = 1;
	if (!buffer)
		buffer = malloc(1);
	buff_supp = malloc(BUFFER_SIZE + 1);
	if (buff_supp == NULL)
		return (NULL);
	while (buff_count > 1)
	{
		buff_count += read(fd, buff_supp, BUFFER_SIZE);
		if (buff_count <= 0)
		{
			free (buff_supp);
			return (NULL);
		}
		buff_supp[buff_count] = '\0';
		buffer = ft_strjoin(buffer, buff_supp);
	}
	free(buff_supp);
	return(buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	buffer = textF_read(buffer, fd);
	if (!buffer)
		return (NULL);
	line = get_line();
	buffer = next_line();	
	return (line);
}


int	main(void)
{
	int	fd;
	char	*line;

	fd = open("song.txt", O_RDONLY);

	int i = fd;
	if (fd < 0)
	{
		printf("Error");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("Value of fd: %d", fd);
	close(fd);
	return (0);
}
