/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:58:45 by Camille           #+#    #+#             */
/*   Updated: 2025/12/14 10:58:17 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		fill_stash(char **stash, char *buf);
static char		*extract_line(char **stash, int fd, bool free_stash);
static ssize_t	read_and_set_buf(char **buf, int fd);

char	*get_next_line(int fd, bool free_stash)
{
	static char	*stash[1024];
	char		*buf;
	char		*line;
	ssize_t		size_read;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	line = NULL;
	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	size_read = 1;
	while (size_read > 0)
	{
		size_read = read_and_set_buf(&buf, fd);
		if (!fill_stash(&stash[fd], buf))
			break ;
		if (ft_strchr(stash[fd], '\n'))
			break ;
	}
	free(buf);
	if (size_read >= 0)
		line = extract_line(&stash[fd], fd, free_stash);
	return (line);
}

static int	fill_stash(char **stash, char *buf)
{
	char	*old_stash;

	old_stash = *stash;
	if (!*stash)
		*stash = ft_strjoin("", buf);
	else
		*stash = ft_strjoin(*stash, buf);
	if (old_stash)
		free(old_stash);
	if (!*stash)
		return (0);
	return (1);
}

static char	*extract_line(char **stash, int fd, bool free_stash)
{
	char	*old_stash;
	char	*line;
	char	*end_of_line;

	if (!*stash)
		return (NULL);
	line = NULL;
	end_of_line = ft_strchr(*stash, '\n');
	if (!end_of_line || fd == 0 || free_stash)
	{
		if (**stash)
			line = ft_substr(*stash, 0, ft_strlen(*stash));
		free(*stash);
		*stash = NULL;
	}
	else
	{
		line = ft_substr(*stash, 0, end_of_line - *stash + 1);
		old_stash = *stash;
		*stash = ft_substr(end_of_line, 1, ft_strlen(*stash));
		free(old_stash);
	}
	return (line);
}

static ssize_t	read_and_set_buf(char **buf, int fd)
{
	ssize_t	size_read;

	size_read = read(fd, *buf, (size_t)BUFFER_SIZE);
	if (size_read < 0)
	{
		free(*buf);
		*buf = NULL;
	}
	else
		(*buf)[size_read] = '\0';
	return (size_read);
}
