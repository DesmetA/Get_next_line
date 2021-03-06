/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesmet <adesmet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:30:56 by adesmet           #+#    #+#             */
/*   Updated: 2021/02/12 12:02:34 by adesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_free(char *tbf)
{
	free(tbf);
	tbf = NULL;
	return (1);
}

int		ft_nl(char *str)
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

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(ptr = (char *)ft_calloc(sizeof(char), (size + 1))))
		return (NULL);
	ft_memmove(ptr, s1, ft_strlen(s1));
	ft_memmove(ptr + ft_strlen(s1), s2, ft_strlen(s2));
	free(s1);
	s1 = NULL;
	return (ptr);
}

int		get_next_line(int fd, char **line)
{
	static char	*stack[OPEN_MAX];
	char		*heap;
	int			tab[2];

	if (fd < 0 || !(line) || fd > OPEN_MAX || BUFFER_SIZE < 1
		|| !(heap = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (stack[fd] && (((tab[1] = ft_nl(stack[fd])) != -1)) && ft_free(heap))
		return (ft_get_line(stack[fd], line, tab[1]));
	while ((tab[0] = read(fd, heap, BUFFER_SIZE)) > 0)
	{
		heap[tab[0]] = '\0';
		stack[fd] = ft_join(stack[fd], heap);
		if (((tab[1] = ft_nl(stack[fd])) != -1) && ft_free(heap))
			return (ft_get_line(stack[fd], line, tab[1]));
	}
	if (stack[fd])
	{
		((*line = ft_strdup(stack[fd])) && ft_free(heap));
		free(stack[fd]);
		stack[fd] = NULL;
		return (tab[0]);
	}
	((*line = ft_strdup("")) && ft_free(heap));
	return (tab[0]);
}
