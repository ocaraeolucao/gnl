/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvieira <luvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:41:57 by luvieira          #+#    #+#             */
/*   Updated: 2026/06/08 21:21:48 by luvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	ssize_t	readfile;
	char	*buf;
	char	*line;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = "";
	while (!ft_strchr(line, '\n') && readfile != 0)
	{
		readfile = read(fd, buf, BUFFER_SIZE);
		if (readfile < 0)
		{
			free(buf);
			free(line);
			return (NULL);
		}
		temp = ft_strjoin(line, buf);
		free(line);
		line = temp;
		buf[readfile] = '\0';
	}
}
