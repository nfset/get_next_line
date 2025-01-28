/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:46:58 by apieniak          #+#    #+#             */
/*   Updated: 2025/01/28 18:01:33 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = my_calloc(ft_strlen(buffer) - i, 1);
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*get_line_main(char *buff)
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

	if (!buffer)
		buffer = my_calloc(1, 1);
	buff_supp = my_calloc(BUFFER_SIZE + 1, 1);
	buff_count = read(fd, buff_supp, BUFFER_SIZE);
	while (buff_count > 0)
	{
		buff_supp[buff_count] = '\0';
		buffer = ft_strjoin(buffer, buff_supp);
		if (!buffer)
			free(buff_supp);
		if (!buffer)
			return (NULL);
		if (search_for_char(buffer, '\n'))
			break ;
		buff_count = read(fd, buff_supp, BUFFER_SIZE);
	}
	free(buff_supp);
	if (buff_count == -1)
		free(buffer);
	if (buff_count == -1)
		buffer = NULL;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = textf_read(buffer, fd);
	if (!buffer)
	{
		buffer = NULL;
		return (NULL);
	}
	line = get_line_main(buffer);
	buffer = next_line(buffer);	
	return (line);
}

