/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saydilek <saydilek@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 09:18:57 by saydilek          #+#    #+#             */
/*   Updated: 2026/09/03 20:48:17 by saydilek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h> //delete
#define BUFFER_SIZE 42

char	*ft_strjoin(char *s1, char *s2);
char	*ft_find_newline(char *s);
int	ft_strlen(char *s);

#endif