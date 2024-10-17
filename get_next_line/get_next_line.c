/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:35:46 by gsantill          #+#    #+#             */
/*   Updated: 2024/10/17 14:05:35 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_read_line(int fd, char *line_buf)
{
	ssize_t read_size;
	char	*aux;
	char	*temp_buf;
	
	read_size = 1;
	temp_buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buf)
		return (NULL);
	while (read_size > 0 && !ft_strchr(temp_buf, '\n'))
	{
		read_size = read(fd, temp_buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		if (read_size == 0)
			break;
		temp_buf[read_size] = '\0';
		if (!line_buf)
			line_buf = ft_strdup("");
		aux = line_buf;
		line_buf = ft_strjoin(line_buf, temp_buf);
		if (!line_buf)
			free(aux);
	}
	free(temp_buf);
	return (line_buf);
}
static char	*ft_extract_remainder(char *line)
{
	size_t	i;
	char	*remainder;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	remainder = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	if (!remainder || remainder[0] == '\0')
	{
		free(remainder);
		return NULL;
	}
	line[i + 1] = '\0';
	return (remainder);
}
char	*ft_get_next_line(int fd)
{
	static char	*line_buf;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read_line(fd, line_buf);
	if (!line)
		return (NULL);
	line_buf = ft_extract_remainder(line);
	return (line);
}
