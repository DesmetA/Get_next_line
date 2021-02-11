/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesmet <adesmet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:30:23 by adesmet           #+#    #+#             */
/*   Updated: 2021/02/11 20:46:53 by adesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = -1;
	if (!(ptr = malloc(sizeof(char) * (size * nmemb))))
		return (NULL);
	while (++i < size * nmemb)
		ptr[i] = '\0';
	return (ptr);
}

void	*ft_memmove(void *dest, void *src, size_t len)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	i = -1;
	if (ptr < ptr2)
	{
		while (++i < len)
			ptr[i] = ptr2[i];
	}
	if (ptr > ptr2)
	{
		while (len--)
			ptr[len] = ptr2[len];
	}
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	char	*s2;
	size_t	i;

	i = -1;
	if (!(s2 = (char *)(ft_calloc(sizeof(char), ft_strlen(s) + 1))))
		return (NULL);
	while (s[++i])
		s2[i] = s[i];
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	len2;

	len2 = len;
	if (!s)
		return (NULL);
	if (ft_strlen(s) - start + 1 < len)
		len2 = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
	{
		if (!(ptr = (char *)ft_calloc(sizeof(char), 1)))
			return (NULL);
		return (ptr);
	}
	if (!(ptr = ft_calloc(sizeof(char), len2 + 1)))
		return (NULL);
	i = -1;
	while (++i < len2)
		ptr[i] = s[start + i];
	return (ptr);
}
