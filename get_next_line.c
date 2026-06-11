/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvieira <luvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:41:57 by luvieira          #+#    #+#             */
/*   Updated: 2026/06/10 21:17:45 by luvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*abortgnl(char *line, char *buf)
{
	free(line);
	free(buf);
	return (NULL);
}

static char	*joinbuf(char *line, char *buf)
{
	char	*temp;

	temp = ft_strjoin(line, buf);
	free(line);
	return (temp);
}

static void	substr(char **line, char **dump, size_t counter)
{
	char	*temp;
	size_t	dumpcount;

	dumpcount = ft_strlen(*line) - counter;
	if (ft_strchr(*line, '\n'))
	{
		*dump = ft_substr(*line, counter, dumpcount);
		temp = ft_substr(*line, 0, counter);
		free(*line);
		*line = temp;
	}
	else
		free(*dump);
}

static char	*setline(char *dump, int fd)
{
	ssize_t			readfile;
	char			*line;
	char			*buf;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = dump;
	if (!line)
	{
		line = (char *)malloc(1);
		line[0] = '\0';
	}
	readfile = 1;
	while (!ft_strchr(line, '\n') && readfile != 0)
	{
		readfile = read(fd, buf, BUFFER_SIZE);
		if (readfile < 0)
			return (abortgnl(line, buf));
		buf[readfile] = '\0';
		line = joinbuf(line, buf);
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	size_t			counter;
	static char		*dump;
	char			*line;

	line = setline(dump, fd);
	if (!line)
	{
		dump = NULL;
		return (NULL);
	}
	counter = 0;
	if (ft_strchr(line, '\n'))
		while (line[counter] != '\n')
			counter++;
	dump = NULL;
	substr(&line, &dump, counter + 1);
	if (line[0] == '\0')
	{
		free(line);
		line = NULL;
	}
	return (line);
}
