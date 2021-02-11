/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areheis <areheis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:31:53 by areheis           #+#    #+#             */
/*   Updated: 2020/12/06 14:47:34 by areheis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <limits.h>

int		get_next_line(int fd, char **line);
char	*ft_strdup(const char *src);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_substr(char const *src, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dst, const void *src, size_t len);
#endif
