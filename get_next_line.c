/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:11:16 by antoniof          #+#    #+#             */
/*   Updated: 2024/11/16 13:55:42 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*move_stored(char *stored)
{
	char	*ret;
	char	*ptr;
	int		len;

	ptr = ft_strchr(stored, '\n');
	if (!ptr)
	{
		ret = NULL;
		return (ft_free(&stored));
	}
	else
		len = (ptr - stored) + 1;
	if (!stored[len])
		return (ft_free(&stored));
	ret = ft_substr(stored, len, ft_strlen(stored) - len);
	ft_free(&stored);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*new_line(char *storage)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	len = (ptr - storage) + 1;
	line = ft_substr(storage, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*readbuf(int fd, char *stored)
{
	int		cread;
	char	*buffer;

	cread = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&stored));
	buffer[0] = '\0';
	while (cread > 0 && !ft_strchr(buffer, '\n'))
	{
		cread = read (fd, buffer, BUFFER_SIZE);
		if (cread > 0)
		{
			buffer[cread] = '\0';
			stored = ft_strjoin(stored, buffer);
		}
	}
	free(buffer);
	if (cread == -1)
		return (ft_free(&stored));
	return (stored);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((stored && !ft_strchr(stored, '\n')) || !stored)
		stored = readbuf (fd, stored);
	if (!stored)
		return (NULL);
	line = new_line(stored);
	if (!line)
		return (ft_free(&stored));
	stored = move_stored(stored);
	return (line);
}
