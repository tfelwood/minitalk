/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:07:28 by tfelwood          #+#    #+#             */
/*   Updated: 2022/03/02 10:38:00 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		++i;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_size;

	src_size = ft_strlen(src);
	if (dstsize)
	{
		while (src && *src && dstsize - 1)
		{
			*dst++ = *src++;
			--dstsize;
		}
		*dst = 0;
	}
	return (src_size);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
	}
}

void	ft_rec_putnbr(long long n, int fd)
{
	char	s;

	if (n / 10)
		ft_rec_putnbr (n / 10, fd);
	s = '0' + (char)(n % 10);
	write(fd, &s, 1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	while (len--)
		((unsigned char *)b)[len] = (unsigned char)c;
	return (b);
}