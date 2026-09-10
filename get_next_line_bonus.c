/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saydilek <saydilek@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:09:37 by saydilek          #+#    #+#             */
/*   Updated: 2026/09/10 17:14:31 by saydilek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_chunk(int fd, char *stash, char *buffer, ssize_t *bytes)
{
	char	*temp;

	*bytes = read(fd, buffer, BUFFER_SIZE);
	if (*bytes <= 0)
		return (stash);
	buffer[*bytes] = '\0';
	temp = ft_strjoin(stash, buffer);
	if (!temp)
	{
		*bytes = -1;
		return (stash);
	}
	free(stash);
	return (temp);
}

static char	*ft_read_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(stash);
		return (NULL);
	}
	bytes = 1;
	while (!ft_find_newline(stash) && bytes > 0)
		stash = ft_read_chunk(fd, stash, buffer, &bytes);
	free(buffer);
	if (bytes < 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	char		*temp;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_stash(fd, stash[fd]);
	if (!stash[fd] || !stash[fd][0])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	temp = stash[fd];
	stash[fd] = ft_get_rest(stash[fd]);
	free(temp);
	return (line);
}
