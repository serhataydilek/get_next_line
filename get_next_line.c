/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saydilek <saydilek@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 09:18:21 by saydilek          #+#    #+#             */
/*   Updated: 2026/09/03 19:31:07 by saydilek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	int bytes;
	char buffer[BUFFER_SIZE];
	
	bytes = read(fd,buffer,BUFFER_SIZE - 1);
	while(bytes > 0)
	{
		bytes = read(fd,buffer,BUFFER_SIZE - 1);
		
	}
	buffer[bytes] = '\0';
	
	close (fd);
}

// read line correct
// null there is nothing else to read or an error occurred