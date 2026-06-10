/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvieira <luvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 20:51:46 by luvieira          #+#    #+#             */
/*   Updated: 2026/06/08 21:10:19 by luvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;

	i = 0;
	src_size = ft_strlen(src);
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}

static void	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;
	size_t	dst_size;

	i = 0;
	dst_size = 0;
	src_size = ft_strlen(src);
	while (dst[dst_size] != '\0' && dst_size < size)
		dst_size++;
	if (size <= dst_size)
		return (size + src_size);
	while (src[i] != '\0' && dst_size + i < size - 1)
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	strjoinlen;

	if (!s1 || !s2)
		return (NULL);
	strjoinlen = ft_strlen(s1) + ft_strlen(s2);
	strjoin = (char *)malloc(strjoinlen);
	if (!strjoin)
		return (NULL);
	ft_strlcpy(strjoin, s1, strjoinlen);
	ft_strlcat(strjoin, s2, strjoinlen);
	strjoin[strjoinlen] = '\0';
	return (strjoin);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
