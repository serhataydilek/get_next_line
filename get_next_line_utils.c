/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saydilek <saydilek@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 09:18:49 by saydilek          #+#    #+#             */
/*   Updated: 2026/09/05 16:20:52 by saydilek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_find_newline(char *s)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (&(s[i]));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	char	*start;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	start = result;
	if (s1)
	{
		while (*s1)
			*result++ = *s1++;
	}
	while (*s2)
	{
		*result++ = *s2++;
	}
	*result = '\0';
	return (start);
}

char	*ft_get_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_get_rest(char *stash)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (NULL);
	i++;
	rest = malloc(ft_strlen(stash + i) + 1);
	if (!rest)
		return (NULL);
	j = 0;
	while (stash[i])
	{
		rest[j] = stash[i];
		i++;
		j++;
	}
	rest[j] = '\0';
	return (rest);
}
