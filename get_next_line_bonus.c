/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesmet <adesmet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:30:56 by adesmet           #+#    #+#             */
/*   Updated: 2021/02/11 19:04:21 by adesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_cp(int fd, char **line)
{
	return (fd < 0 || !(line) || fd > OPEN_MAX);
}

int		ft_newline(char *str)
{
	int i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (str[i] == '\n')
			return (i);
	}
	return (-1);
}

int		ft_get_line(char *stack, char **line, int nl)
{
	int i;

	*line = ft_substr(stack, 0, nl);
	nl++;
	i = ft_strlen(stack + nl);
	ft_memmove(stack, stack + nl, i + 1);
	return (1);
}

char	*ft_join(char *s1, char *s2)
{
	char	*ptr;
	int		size;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(ptr = (char *)ft_calloc(sizeof(char), (size + 1))))
		return (NULL);
	ft_memmove(ptr, s1, ft_strlen(s1));
	ft_memmove(ptr + ft_strlen(s1), s2, ft_strlen(s2));
	return (ptr);
}

int		get_next_line(int fd, char **line)
{
	static char	*stack[OPEN_MAX];
	char		*heap;
	int			ret;
	int			nl;

	if (ft_cp(fd, line) || !(heap = malloc((sizeof(char) * BUFFER_SIZE) + 1)))
		return (-1);
	if (stack[fd] && (((nl = ft_newline(stack[fd])) != -1)))
		return (ft_get_line(stack[fd], line, nl));
	while ((ret = read(fd, heap, BUFFER_SIZE)) > 0)
	{
		heap[ret] = '\0';
		stack[fd] = ft_join(stack[fd], heap);
		if ((nl = ft_newline(stack[fd])) != -1)
			return (ft_get_line(stack[fd], line, nl));
	}
	if (stack[fd])
	{
		*line = ft_strdup(stack[fd]);
		free(stack[fd]);
		stack[fd] = NULL;
		return (ret);
	}
	*line = ft_strdup("");
	return (ret);
}
