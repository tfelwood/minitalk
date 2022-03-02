/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:03:34 by tfelwood          #+#    #+#             */
/*   Updated: 2022/03/02 15:03:34 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

int	ft_addchar(t_message *message)
{
	char	*copy;
	int		count;

	count = 0;
	if (!message->size)
		count = 8;
	else if ((int)ft_strlen(message->text) >= message->size - 1)
		count = 2 * message->size;
	if (count)
	{
		copy = (char *) malloc(count * sizeof(char));
		if (!copy)
			return (-1);
		message->size = count;
		ft_strlcpy(copy, message->text, message->size);
		free(message->text);
		message->text = copy;
	}
	count = ft_strlen(message->text);
	message->text[count] = message->symb;
	message->text[count + 1] = 0;
	return (0);
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