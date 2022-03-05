/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:07:28 by tfelwood          #+#    #+#             */
/*   Updated: 2022/03/02 15:15:49 by tfelwood         ###   ########.fr       */
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

void	ft_putstr_fd(const char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
	}
}

int	ft_strtoi(const char *str)
{
	long long	num;

	num = 0;
	if (!str || !*str)
		num = -1;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		++str;
	}
	if (*str)
		num = -1;
	return (num);
}
