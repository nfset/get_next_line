/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:46:58 by apieniak          #+#    #+#             */
/*   Updated: 2025/01/20 16:06:14 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 42
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	// find len of first line
	while (buffer[i] && buffer[i] != '\n')
		i++;
	// if eol == \0 return NULL
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	// len of file - len of firstline + 1
	line = malloc((ft_strlen(buffer) - i + 1));
	i++;
	j = 0;
	// line == buffer
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*get_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = malloc(i + 2);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*textf_read(char *buffer, int fd)
{
	char	*buff_supp;
	int		buff_count;

	buff_count = 1;
	if (!buffer)
		buffer = malloc(1);
	buff_supp = malloc(BUFFER_SIZE + 1);
	if (!buff_supp)
		return (NULL);
	while (buff_count > 0)
	{
		buff_count += read(fd, buff_supp, BUFFER_SIZE);
		if (buff_count == -1)
		{
			free(buff_supp);
			return (NULL);
		}
		buff_supp[buff_count] = 0;
		buffer = ft_strjoin(buffer, buff_supp);
		if (search_for_char(buffer, '\n'))
			break ;
	}
	free(buff_supp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	buffer = textf_read(buffer, fd);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = next_line(buffer);	
	return (line);
}


int	main(void)
{
	//int		d;
	char	*line;
	int fd;

	fd = open("text.txt", O_RDONLY);
	//int i = fd;
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
