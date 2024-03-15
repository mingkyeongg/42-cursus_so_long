/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:25:02 by minkylee          #+#    #+#             */
/*   Updated: 2023/06/15 17:35:35 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*free_store(char **store)
{
	free(*store);
	*store = NULL;
	return (NULL);
}

char	*ft_get_line(int fd, char *buf, char **store, int read_line)
{
	char	*temp;

	while (!ft_strchr(*store, '\n') && read_line)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (free_store(store));
		buf[read_line] = '\0';
		temp = *store;
		*store = ft_strjoin(temp, buf);
		if (!*store)
		{
			free_store(&temp);
			return (free_store(store));
		}
		free_store(&temp);
	}
	if ((*store)[0] == '\0')
		return (free_store(store));
	return (*store);
}

char	*ft_separation(char *line)
{
	int		index;
	char	*result;

	index = 0;
	while (line[index] != '\n' && line[index])
		index++;
	if (!line[index])
		return (NULL);
	result = ft_substr(line, index + 1, ft_strlen(line) - index);
	if (!result)
		return (NULL);
	if (result[0] == '\0')
	{
		free_store(&result);
		return (NULL);
	}
	line[index + 1] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = ft_get_line(fd, buf, &store, 1);
	free_store(&buf);
	if (!line)
		return (NULL);
	store = ft_separation(line);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main(void)
// {
//   int fd;
//   char *line;

//   fd = 0;
//   fd = open("/Users/minkylee/Desktop/minkylee/so_long/hi", O_RDONLY);
//   while ((line = get_next_line(fd)) != NULL)
//   {
//   	printf("%s", line);
// 	  free(line);
//   }
//   if (line == NULL)
// 		printf("%s\n", line);

//   close(fd);

//   return (0);
// }