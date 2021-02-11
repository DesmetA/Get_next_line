/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesmet <adesmet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 21:01:50 by adesmet           #+#    #+#             */
/*   Updated: 2021/02/11 22:10:27 by adesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_cp(int fd, char **line)
{
	return (fd < 0 || !(line) || fd > FOPEN_MAX || BUFFER_SIZE < 1);
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
	static char	*stack;
	char		heap[BUFFER_SIZE +1];
	int			ret;
	int			nl;

	if (ft_cp(fd, line))
		return (-1);
	if (stack && (((nl = ft_newline(stack)) != -1)))
		return (ft_get_line(stack, line, nl));
	while ((ret = read(fd, heap, BUFFER_SIZE)) > 0)
	{
		heap[ret] = '\0';
		stack = ft_join(stack, heap);
		if ((nl = ft_newline(stack)) != -1)
			return (ft_get_line(stack, line, nl));
	}
	if (stack)
	{
		*line = ft_strdup(stack);
		free(stack);
		stack = NULL;
		return (ret);
	}
	*line = ft_strdup("");
	return (ret);
}

int main(int argc, char **argv)
{
    int fd;
    int ret;
    char *line;
    ret = 1;
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        while ((ret = get_next_line(fd, &line)) > 0)
        {
            printf("%s\n", line);
            free(line);
        }
        printf("%s\n", line);
        printf("%d",ret);
        if (ret == -1)
        printf("-----------\n An error happened\n");
        else if (ret == 0)
        {
            printf("-----------\n EOF has been reached\n");
            free(line);
        }
        close(fd);
    }
    printf("gnl returned %d", ret);
    return (0);
}