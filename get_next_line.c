/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areheis <areheis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:31:02 by areheis           #+#    #+#             */
/*   Updated: 2020/12/06 16:19:52 by areheis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_index(const char *str, int c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] != (char)c)
		return (-1);
	return (i);
}

int		get_line(char *str, char **line, int i)
{
	int len;

	*line = ft_substr(str, 0, i);
	i++;
	len = ft_strlen(str + i) + 1;
	ft_memmove(str, str + i, len);
	return (1);
}

char	*protect_dup(char *str)
{
	char *line;

	if (!(line = ft_strdup(str)))
		return ((char *)-1);
	return (line);
}

char	*protect_join_free(char *s1, char *s2)
{
	char *stri;

	if (!(stri = ft_strjoin_free(s1, s2)))
		return ((char *)-1);
	return (stri);
}

int		get_next_line(int fd, char **line)
{
	char			tmp[BUFFER_SIZE + 1];
	static char		*str = NULL;
	int				in[2];

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, tmp, 0) < 0
	|| fd > OPEN_MAX)
		return (-1);
	if (str && (((in[0] = find_index(str, '\n')) != -1)))
		return (get_line(str, line, in[0]));
	while (((in[1] = read(fd, tmp, BUFFER_SIZE)) > 0))
	{
		tmp[in[1]] = '\0';
		str = protect_join_free(str, tmp);
		if (((in[0] = find_index(str, '\n')) != -1))
			return (get_line(str, line, in[0]));
	}
	if (str)
	{
		*line = protect_dup(str);
		free(str);
		str = NULL;
		return (in[1]);
	}
	*line = protect_dup("");
	return (in[1]);
}
