/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:46:58 by apieniak          #+#    #+#             */
/*   Updated: 2025/01/22 15:55:14 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = my_calloc(ft_strlen(buffer) - i + 1, 1);
	i++;
	j = 0;
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
	line = my_calloc(i + 2, 1);
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
		buffer = my_calloc(1, 1);
	buff_supp = my_calloc(BUFFER_SIZE + 1, 1);
	while (buff_count > 0)
	{
		buff_count = read(fd, buff_supp, BUFFER_SIZE);
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

