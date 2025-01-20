/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:01:00 by apieniak          #+#    #+#             */
/*   Updated: 2025/01/20 15:41:14 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>


int		search_for_char(char *str, char sign);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *src, char *dest);
char	*next_line(char *buff);
char	*get_line(char *buff);
char	*textf_read(char *buffer, int fd);
char	*get_next_line(int fd);

#endif
