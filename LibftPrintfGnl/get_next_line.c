/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:23:32 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/03 02:16:21 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include "../so_long.h"

/*
	Reads from the file and appends new data to any previously stored data
	until a newline or EOF (end of file) is reached.
	@return A newly allocated string containing updated(modified) stored_data.
*/
static char	*read_and_append(int fd, char *buffer, char *stored_data)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stored_data)
			stored_data = ft_strjoin("", "");
		temp = stored_data;
		stored_data = ft_strjoin(temp, buffer);
		free(temp);
		if (!stored_data)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stored_data);
}

/*
	Extracts the next full line from stored_data.
	Updates stored_data to contain only the remaining text after the line.
	@return A newly allocated string containing the extracted line.
 */
static char	*extract_current_line(char *full_data)
{
	size_t	index;
	char	*remaining_data;

	index = 0;
	while (full_data[index] && full_data[index] != '\n')
		index++;
	if (full_data[index] == '\0')
		return (0);
	remaining_data = ft_substr(full_data, index + 1, ft_strlen(full_data)
			- index - 1);
	if (!remaining_data)
		return (NULL);
	if (!remaining_data || *remaining_data == '\0')
	{
		free(remaining_data);
		remaining_data = NULL;
	}
	full_data[index + 1] = '\0';
	return (remaining_data);
}
/*
	Reads the next line from the given fd (file descriptor)
	Uses a static variable to store remaining data between function calls
	@return A newly allocated string containing the next line, or NULL if EOF.
 */

char	*get_next_line(int fd)
{
	char		*current_line;
	char		*buffer;
	static char	*stored_data;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	current_line = read_and_append(fd, buffer, stored_data);
	free(buffer);
	if (!current_line)
		return (NULL);
	stored_data = extract_current_line(current_line);
	return (current_line);
}
