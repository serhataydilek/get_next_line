/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saydilek <saydilek@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 09:18:21 by saydilek          #+#    #+#             */
/*   Updated: 2026/09/05 16:20:58 by saydilek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*stash;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_stash(fd, stash);
	if (!stash || !stash[0])
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_get_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	temp = stash;
	stash = ft_get_rest(stash);
	free(temp);
	return (line);
}
// read line correct
// null there is nothing else to read or an error occurred